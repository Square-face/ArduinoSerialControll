import Command

def init_test():
    cmd = Command.Command("digitalWrite", 3, True)

    assert cmd.type == "digitalWrite"
    assert cmd.pin == 3
    assert cmd.digital_value == True


def set_test():
    cmd = Command.Command().set_type("test").set_pin(2).set_value(255)

    assert cmd.type == "test"
    assert cmd.pin == 2
    assert cmd.analog_value == 255

    cmd.set_value(True)

    assert cmd.digital_value == True

def stringify_test():
    cmd = Command.Command("digitalWrite", 4, True)
    assert cmd.stringify() == '{"origin":"master","type":"digitalWrite","pin":4,"value":true}'

    cmd = Command.Command("analogWrite", 5, analog_value=127)
    assert cmd.stringify() == '{"origin":"master","type":"analogWrite","pin":5,"value":127}'

    cmd = Command.Command("digitalRead", 13)
    assert cmd.stringify() == '{"origin":"master","type":"digitalRead","pin":13}'

    cmd = Command.Command("analogRead", 7)
    assert cmd.stringify() == '{"origin":"master","type":"analogRead","pin":7}'


tests = [init_test, set_test, stringify_test]
if __name__ == "__main__":
    print("Testing...")
    for test in tests:
        test()
        print(f"Test {tests.index(test)+1}/{len(tests)} passed")
    print("All tests passed")
