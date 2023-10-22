# plot_k_values.py

import matplotlib.pyplot as plt
import sys

# Get errors from command line arguments
errors = [float(e) for e in sys.argv[1:]]

plt.figure(figsize=(10, 6))
plt.plot(range(1, len(errors) + 1), errors, marker='o', linestyle='--')
plt.title('Accuracy vs. K Value')
plt.xlabel('K Value')
plt.ylabel('Accuracy')
plt.xticks(range(1, len(errors) + 1))
plt.grid(True)
plt.show()
