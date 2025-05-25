import matplotlib.pyplot as plt

def plot_results(input_file, output_file, title, xlabel, ylabel, xticks_label, col):
    x = []
    winner_tree_times = []
    binary_heap_times = []

    try:
        with open(input_file, 'r') as file:
            next(file)
            for line in file:
                cols = line.strip().split('\t')
                x.append(int(cols[0]))
                winner_tree_times.append(float(cols[2-col]))
                binary_heap_times.append(float(cols[3-col]))
    except IOError as e:
        print(f"Ошибка чтения файла: {e}")
        return

    if not x or not winner_tree_times or not binary_heap_times:
        print("Ошибка: пустые данные для построения графика!")
        return

    plt.figure(figsize=(16, 9))
    plt.plot(x, winner_tree_times, marker='o', color="#80ff00", label="Winner Max Tree")
    plt.plot(x, binary_heap_times, marker='s', color="#db34eb", label="Binary Heap")
    plt.title(title, fontsize=16)
    plt.xlabel(xlabel, fontsize=14)
    plt.ylabel(ylabel, fontsize=14)
    plt.xscale("log", base=2) if col > 0 else None
    plt.yscale("log") if col > 0 else None
    plt.xticks(x)
    plt.grid(True, linestyle="--", linewidth=0.5, color="#cccccc")
    plt.legend(loc="upper left", fontsize=12)
    plt.tight_layout()
    plt.savefig(output_file)
    print(f"График сохранён в {output_file}")

if __name__ == "__main__":
    # Plot for 1.txt
    plot_results(
        input_file="First.txt",
        output_file="plot_1.png",
        title="Сравнение Winner Max Tree и Binary Heap в k-way merge",
        xlabel="Количество массивов",
        ylabel="Время работы (секунды)",
        xticks_label="Количество массивов",
        col=0
    )

    # Plot for 2.txt
    plot_results(
        input_file="Second.txt",
        output_file="plot_2.png",
        title="Сравнение Winner Max Tree и Binary Heap",
        xlabel="Размер массивов",
        ylabel="Время работы (секунды, логарифм)",
        xticks_label="Размер массивов",
        col=1
    )
