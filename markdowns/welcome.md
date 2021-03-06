# Welcome!

This Basic template lets you get started quickly with a simple working example. If it is your first contribution then you should have a look at the [Getting Started](https://tech.io/doc/getting-started-create-playground) document.


Please refer to the [documentation](https://tech.io/doc) to learn more about adding programming exercises within your contribution.

@[test csv]({"stubs": ["cpp_param_test.cpp", "input.csv", "correct_output.csv"],"command": "sh ./run_with_param.sh cpp_param_test.cpp input.csv city London output.csv"})

@[makeInvestment]({"stubs": ["cpp_makeInvestment.cpp"],"command": "sh ./run.sh cpp_makeInvestment.cpp"})

@[close_enough ]({"stubs": ["cpp_close_enough.cpp"],"command": "sh ./run.sh cpp_close_enough.cpp"})

@[std::optional refactor ]({"stubs": ["cpp_refactor_into_optional.cpp"],"command": "sh ./run.sh cpp_refactor_into_optional.cpp"})


## JFT guest post:

@[JFT's menu example]({"stubs": ["cpp_jft_menu.cpp"],"command": "sh ./run_with_terminal.sh cpp_jft_menu.cpp"})

## `from_chars`:

@[`std::from_chars` Example]({"stubs": ["cpp_from_chars.cpp"],"command": "sh ./run.sh cpp_from_chars.cpp"})

## `file_size`:

@[`fs::file_size` Example]({"stubs": ["cpp_file_size.cpp"],"command": "sh ./run_filesystem.sh cpp_file_size.cpp"})

## `file_size` Permissions:

@[`fs::file_size` Permission Example]({"stubs": ["cpp_file_size_perms.cpp"],"command": "sh ./run_filesystem.sh cpp_file_size_perms.cpp"})

## overload:

@[overload pattern Example]({"stubs": ["cpp_overload.cpp"],"command": "sh ./run.sh cpp_overload.cpp"})

## dbg move:

@[Debug Move]({"stubs": ["cpp_move_dbg.cpp"],"command": "sh ./run.sh cpp_move_dbg.cpp"})

@[Debug Move - Custom Type]({"stubs": ["cpp_move_dbg_type.cpp"],"command": "sh ./run.sh cpp_move_dbg_type.cpp"})

## new new()

@[Custom New With Alignment]({"stubs": ["cpp_new.cpp"],"command": "sh ./run.sh cpp_new.cpp"})

## IIFE

@[IIFE C++ Example]({"stubs": ["cpp_iife.cpp"],"command": "sh ./run.sh cpp_iife.cpp"})

## Lazy Init

@[Lazy initialisation]({"stubs": ["cpp_lazy_worker.cpp"],"command": "sh ./run_pthread.sh cpp_lazy_worker.cpp"})

## Wehicle Generator

@[Wehicle Generator]({"stubs": ["cpp_wehicle_generator.cpp", "wehicle_parts.txt"],"command": "sh ./run_with_param_no_check.sh cpp_wehicle_generator.cpp wehicle_parts.txt"})

# Template Resources

[`markdowns/welcome.md`](https://github.com/TechDotIO/techio-basic-template/blob/master/markdowns/welcome.md)  
What you are reading here is generated by this file. Tech.io uses the [Markdown syntax](https://tech.io/doc/reference-markdowns) to render text, media and to inject programming exercises.


[`techio.yml`](https://github.com/TechDotIO/techio-basic-template/blob/master/techio.yml)  
This *mandatory* file describes both the table of content and the programming project(s). The file path should not be changed.