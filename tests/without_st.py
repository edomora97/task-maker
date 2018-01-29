#!/usr/bin/env python3

# we use the global scope, so pylint considers every variable as a constant
# pylint: disable=invalid-name

from proto.event_pb2 import DONE

from tests.test import run_tests, TestingUI


# pylint: disable=protected-access


def test_task_details() -> None:
    test_data = TestingUI.inst
    assert test_data.task_name == "Testing task-maker (without_st)"
    assert test_data._time_limit == 1
    assert test_data._memory_limit == 65536
    assert test_data._num_testcases == 6

    assert len(test_data._subtask_testcases) == 1
    assert list(test_data._subtask_testcases[0]) == [0, 1, 2, 3, 4, 5]
    assert len(test_data._subtask_max_scores) == 1
    assert test_data._subtask_max_scores[0] == 100


def test_generation() -> None:
    test_data = TestingUI.inst
    assert not test_data._generation_errors
    for gen_status in test_data._generation_status.values():
        assert gen_status == DONE


def test_solutions() -> None:
    test_data = TestingUI.inst
    soluzione = test_data._solution_status["soluzione.py"]
    assert soluzione.score == 100
    for testcase in soluzione.testcase_result.values():
        assert testcase.message == "Output is correct"
        assert testcase.score == 1


if __name__ == "__main__":
    run_tests("without_st", __file__)
