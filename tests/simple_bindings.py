#!/usr/bin/env python3
import tempfile
from bindings import Core


def callback(data: Core.TaskStatus) -> bool:
    print(data.event, data.message, data.type)
    return data.event != Core.TaskStatus.Event.FAILURE


def main() -> None:
    with tempfile.NamedTemporaryFile() as tmp:
        tmp.write(b"Lorem ipsum dolor sit amet.")
        tmp.seek(0)

        exec_core = Core()
        exec_core.set_callback(callback)
        temp_file = exec_core.load_file("tmp file", tmp.name)
        ex = exec_core.add_execution("test", "/bin/cat", ["foobar"])
        ex.input("foobar", temp_file)
        assert exec_core.run()
        assert ex.stdout().contents(100) == "Lorem ipsum dolor sit amet."
        assert ex.stderr().contents(100) == ""


if __name__ == '__main__':
    main()