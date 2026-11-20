import matplotlib.pyplot as plt
import os

frames = list(range(3, 11))

random_data = {
    "FIFO": [95383, 93836, 92262, 90667, 89128, 87541, 86057, 84480],
    "LRU": [95394, 93832, 92273, 90683, 89105, 87566, 86029, 84492],
    "Optimal": [81610, 76388, 71993, 68191, 64794, 61694, 58850, 56208]
}

locality_data = {
    "FIFO": [69125, 59681, 50853, 42739, 35685, 29986, 25551, 22224],
    "LRU": [68750, 58665, 49158, 39665, 30869, 22977, 16767, 12797],
    "Optimal": [47461, 36199, 27572, 20748, 15382, 11295, 8524, 7621]
}

os.makedirs("outputs", exist_ok=True)

for workload, data in [
    ("Random", random_data),
    ("Locality", locality_data)
]:
    plt.figure(figsize=(9, 6))

    for algorithm, faults in data.items():
        plt.plot(frames, faults, marker="o", label=algorithm)

    plt.title(f"Page Faults vs Number of Frames - {workload} Workload")
    plt.xlabel("Number of Frames")
    plt.ylabel("Number of Page Faults")
    plt.xticks(frames)
    plt.grid(True)
    plt.legend()
    plt.tight_layout()

    filename = f"outputs/Task05_{workload}_Page_Fault_Graph.png"
    plt.savefig(filename, dpi=200)
    plt.close()

    print("Graph saved:", filename)

