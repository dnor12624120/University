from Service import Service

config = {}

with open('config.txt', 'r') as f:
    for line in f:
        config[line.split()[0]] = line.split()[-1]


service = Service(int(config['runs']),
                  int(config['colony_size']),
                  int(config['iterations']),
                  int(config['size']),
                  float(config['alpha']),
                  float(config['beta']),
                  float(config['rho']),
                  float(config['q0']),
                  float(config['pheromone_amount']),
                  float(config['tau']),
                  float(config['default_trace']))

service.run()
