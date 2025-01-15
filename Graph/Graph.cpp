#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <random>
using namespace std;

// Структура для хранения ребра 
struct Edge
{
    size_t TargetNode; // Целевая вершина
    int Weight;        // Вес ребра
};

// Структура для хранения информации о вершине
struct Node
{
    size_t Index;          // Индекс вершины
    int Distance;          // Текущее расстояние до вершины
};

// Компаратор для приоритетной очереди
struct CompareDistance
{
    bool operator()(const Node& a, const Node& b)
    {
        return a.Distance > b.Distance;
    }
};

/**
 * Вывод всех рёбер графа (пар соседних вершин и расстояний между ними).
 *
 * @param Graph Граф в виде списка смежности.
 */
void PrintGraphEdges(const vector<vector<Edge>>& Graph)
{
    size_t NumNodes = Graph.size();
    cout << "Рёбра графа (пары соседних вершин и расстояния):\n";

    for (size_t i = 0; i < NumNodes; ++i)
    {
        for (const Edge& Neighbor : Graph[i])
        {
            if (i < Neighbor.TargetNode)
            {
                cout << "  Вершина " << i << " -> Вершина " << Neighbor.TargetNode << ": " << Neighbor.Weight << "\n";
            }
        }
    }
}

/**
 * Реализация алгоритма Дейкстры для поиска кратчайших путей от начальной вершины до всех остальных.
 *
 * @param Graph Вектор векторов рёбер, представляющий граф.
 * @param StartNode Начальная вершина.
 * @return Вектор с расстояниями от начальной вершины до всех остальных.
 */
vector<int> DijkstraAlgorithm(const vector<vector<Edge>>& Graph, size_t StartNode)
{
    size_t NumNodes = Graph.size();
    vector<int> Distances(NumNodes, numeric_limits<int>::max()); // Инициализация расстояний
    Distances[StartNode] = 0;

    // Приоритетная очередь для выбора вершины с минимальным расстоянием
    priority_queue<Node, vector<Node>, CompareDistance> PriorityQueue;
    PriorityQueue.push({ StartNode, 0 });

    while (!PriorityQueue.empty())
    {
        Node CurrentNode = PriorityQueue.top();
        PriorityQueue.pop();

        size_t CurrentIndex = CurrentNode.Index;

        // Если текущее расстояние больше, чем уже найденное, пропускаем
        if (CurrentNode.Distance > Distances[CurrentIndex])
        {
            continue;
        }

        // Обход всех соседей текущей вершины
        for (const Edge& Neighbor : Graph[CurrentIndex])
        {
            int NewDistance = Distances[CurrentIndex] + Neighbor.Weight;

            // Если найден более короткий путь, обновляем расстояние
            if (NewDistance < Distances[Neighbor.TargetNode])
            {
                Distances[Neighbor.TargetNode] = NewDistance;
                PriorityQueue.push({ Neighbor.TargetNode, NewDistance });
            }
        }
    }

    return Distances;
}

/**
 * Генерация случайного графа.
 *
 * @param NumNodes Количество вершин в графе.
 * @return Сгенерированный граф в виде списка смежности.
 */
vector<vector<Edge>> GenerateRandomGraph(size_t NumNodes)
{
    vector<vector<Edge>> Graph(NumNodes);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> WeightDist(1, 100);

    for (size_t i = 0; i < NumNodes; ++i)
    {
        for (size_t j = 0; j < NumNodes; ++j)
        {
            if (i != j)
            {
                int Weight = WeightDist(gen);
                Graph[i].push_back({ j, Weight });
            }
        }
    }

    return Graph;
}

int main()
{
    setlocale(LC_ALL, "RU");
    size_t NumNodes, StartNode, TargetNode;

    cout << "Введите количество вершин: ";
    cin >> NumNodes;

    vector<vector<Edge>> Graph = GenerateRandomGraph(NumNodes);

    cout << "Введите начальную вершину (от 0 до " << NumNodes - 1 << "): ";
    cin >> StartNode;

    cout << "Введите целевую вершину (от 0 до " << NumNodes - 1 << "): ";
    cin >> TargetNode;

    // Проверка корректности ввода
    if (StartNode >= NumNodes || TargetNode >= NumNodes)
    {
        cout << "Ошибка: некорректный ввод вершин.\n";
        return 1;
    }

    vector<int> Distances = DijkstraAlgorithm(Graph, StartNode);

    if (Distances[TargetNode] != numeric_limits<int>::max())
    {
        cout << "Кратчайшее расстояние от вершины " << StartNode << " до вершины " << TargetNode << ": " << Distances[TargetNode] << "\n";
    }
    else
    {
        cout << "Путь от вершины " << StartNode << " до вершины " << TargetNode << " не существует.\n";
    }

    // Вывод всех пар вершин и расстояний между ними
    cout << "\nВсе пары вершин и расстояния между ними:\n";
    PrintGraphEdges(Graph);

    return 0;
}