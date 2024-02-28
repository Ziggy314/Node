#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <functional>
#include "headers/Node.hpp"
#include "headers/NodePack.hpp"
#include "headers/Resources.hpp"
#include <thread>


#include <benchmark/benchmark.h>



// static void BM_executeByval(benchmark::State& state) {
//     NodeAccessor accessor = nodeVisitor;
//     Node<Resources> node(TestNode(2));
//     for (auto _ : state)
//     {
//         node.accept(accessor);
//     }
// }


// static void BM_executeSp(benchmark::State& state) {
//     NodeAccessor accessor = spNodeVisitor;
//     auto tn = std::make_shared<TestNode>(2);
//     Node<Resources> node1(tn);
//     for (auto _ : state)
//     {
//         node1.accept(accessor);
//     }
// }
// BENCHMARK(BM_executeByval)->Iterations(1000000);;
// BENCHMARK(BM_executeSp)->Iterations(1000000);


BENCHMARK_MAIN();
