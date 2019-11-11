#include <iostream>
#include <map>
#include <mutex> // for call_once
#include <numeric>
#include <optional>
#include <string>
#include <utility>
#include <vector>
#include <mutex>
#include <thread>

using TSalary = long; // might be replaced into decimal, fixed point type...

class CompanyDatabase {
public:
	struct EmployeeRecord { 
		std::string _name; 
		std::string _surname; 
		std::string _city; 
		TSalary _salary{ 0 };
	};

public:
	size_t MaxEntries() const { return s_table.size(); }
	static constexpr size_t InvalidID = 666;

	EmployeeRecord FetchRecord(int id) const { 
        std::cout << "Fetching record: " << id << '\n';
        return s_table.at(id); 
    }

private:
	static inline const std::vector<EmployeeRecord> s_table{
		{ "John", "Doe", "Cracow", 120 },
		{ "Kate", "Doe", "Cracow", 80 },
		{ "Linda", "Doe", "Warsaw", 140 },
		{ "Marc", "Doe", "Warsaw", 100 }
	};
};

class Employee {
public:
	explicit Employee(size_t id, const CompanyDatabase& db) : _id(id), _db(&db) { }

    std::string Name() const { MakeSureWereReady(); return _rec->_name; }
    std::string Surname() const { MakeSureWereReady(); return _rec->_surname; }
	std::string City() const { MakeSureWereReady(); return _rec->_city; }
	TSalary Salary() const { MakeSureWereReady(); return _rec->_salary; }

	friend std::ostream& operator<<(std::ostream& os, const Employee& em)
	{
		os << em._id << ": " << em.Name() << ", " << em.Surname() << ", " << em.City() << ", " << em.Salary() << '\n';
		return os;
	}
private:
	void MakeSureWereReady() const {
		if (!_rec)
		    _rec = _db->FetchRecord(_id);
	}

	size_t _id{ CompanyDatabase::InvalidID };
	mutable std::optional<CompanyDatabase::EmployeeRecord> _rec;
	const CompanyDatabase* _db;
};

template<typename T>
void SalaryTask(const std::vector<T>& workers) {
    auto SalaryOp = [](TSalary curr, const T& em) {
		return curr + em.Salary();
	};
	const auto sumSalary = std::accumulate(std::cbegin(workers), std::cend(workers), 0, SalaryOp);
	std::cout << "Sum salary: " << sumSalary << '\n';
}

template<typename T>
void CityTask(const std::vector<T>& workers) {
	std::map<std::string, int> mapByCity;
	for (auto& em : workers)
		mapByCity[em.City()]++;

	for (const auto& [city, num] : mapByCity)
		std::cout << city << ": " << num << '\n';
}

template<typename T>
void WorkerTest() {
    std::cout << "sizeof: " << sizeof(T) << '\n';
    CompanyDatabase db;
	std::vector<T> workers;
	for (size_t i = 0; i < db.MaxEntries(); ++i)
		workers.emplace_back(T{ i, db });
    
    std::thread t1(SalaryTask<T>, std::cref(workers));
    std::thread t2(CityTask<T>, std::cref(workers));
    t1.join();
    t2.join();
}

class EmployeeMut {
public:
	explicit EmployeeMut(size_t id, const CompanyDatabase& db) : _id(id), _db(&db) { }
    ~EmployeeMut() { }

    EmployeeMut(const EmployeeMut& other) noexcept : _id(other._id), _db(other._db), _rec(other._rec) { }
    EmployeeMut& operator=(const EmployeeMut& other) noexcept { _id = other._id; _db = other._db; _rec = other._rec; return *this; }
    EmployeeMut(EmployeeMut&& other) noexcept : _id(other._id), _db(other._db), _rec(std::move(other._rec)) { }
    EmployeeMut& operator=(EmployeeMut&& other) noexcept { _id = other._id; _db = other._db; _rec = std::move(other._rec); return *this; }
    
    std::string Name() const { MakeSureWereReady(); return _rec->_name; }
    std::string Surname() const { MakeSureWereReady(); return _rec->_surname; }
	std::string City() const { MakeSureWereReady(); return _rec->_city; }
	TSalary Salary() const { MakeSureWereReady(); return _rec->_salary; }

	friend std::ostream& operator<<(std::ostream& os, const EmployeeMut& em)
	{
		os << em._id << ": " << em.Name() << ", " << em.Surname() << ", " << em.City() << ", " << em.Salary() << '\n';
		return os;
	}
    
private:
	void MakeSureWereReady() const {
        std::scoped_lock lock(mut);
        if (!_rec)
          _rec = _db->FetchRecord(_id);
	}

private:
	size_t _id{ CompanyDatabase::InvalidID };
    const CompanyDatabase* _db;
    
    mutable std::mutex mut;
	mutable std::optional<CompanyDatabase::EmployeeRecord> _rec;	
};

class EmployeeOnce {
public:
	explicit EmployeeOnce(size_t id, const CompanyDatabase& db) : _id(id), _db(&db) { }
    ~EmployeeOnce() { }

    EmployeeOnce(const EmployeeOnce& other) noexcept : _id(other._id), _db(other._db), _rec(other._rec) { }
    EmployeeOnce& operator=(const EmployeeOnce& other) noexcept { _id = other._id; _db = other._db; _rec = other._rec; return *this; }
    EmployeeOnce(EmployeeOnce&& other) noexcept : _id(other._id), _db(other._db), _rec(std::move(other._rec)) { }
    EmployeeOnce& operator=(EmployeeOnce&& other) noexcept { _id = other._id; _db = other._db; _rec = std::move(other._rec); return *this; }
    
    std::string Name() const { MakeSureWereReady(); return _rec->_name; }
    std::string Surname() const { MakeSureWereReady(); return _rec->_surname; }
	std::string City() const { MakeSureWereReady(); return _rec->_city; }
	TSalary Salary() const { MakeSureWereReady(); return _rec->_salary; }

	friend std::ostream& operator<<(std::ostream& os, const EmployeeOnce& em)
	{
		os << em._id << ": " << em.Name() << ", " << em.Surname() << ", " << em.City() << ", " << em.Salary() << '\n';
		return os;
	}
    
private:
	void MakeSureWereReady() const {
		if (!_rec) // might be problematic... double-check-locking...
        {
            std::call_once(_flag, [&]() {
            if (!_rec)
		      _rec = _db->FetchRecord(_id);
            });
        }
	}

private:
	size_t _id{ CompanyDatabase::InvalidID };
    const CompanyDatabase* _db;
    
    mutable std::once_flag _flag;
	mutable std::optional<CompanyDatabase::EmployeeRecord> _rec;	
};

int main() { 
    try {
	   WorkerTest<Employee>();
       WorkerTest<EmployeeMut>();
       WorkerTest<EmployeeOnce>();
    }
    catch (const std::out_of_range& err) {
        std::cerr << "out of range error! " << err.what() << '\n';
    }
}