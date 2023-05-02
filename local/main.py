import yaml, Arduino

def read_config(config_path):
    """Read configuration file"""
    with open(config_path) as yaml_file:
        config = yaml.safe_load(yaml_file)
    return config


if __name__ == "__main__":

    config = read_config('config.yaml')
    Arduino.Arduino(config["port"], config["baudrate"])