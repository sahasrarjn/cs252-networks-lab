import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data = pd.read_csv("data-sahasra.csv", delimiter=';')
rssi = data['rssi']
node_id = data['node_id']

print(np.unique(node_id))



