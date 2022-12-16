class MonkeyProcessor {
  final BigInt Function(BigInt) inspect;
  final List<int> dispatcher;
  final List<BigInt> items;
  final List<int> itemsInput;
  MonkeyProcessor(this.inspect, this.dispatcher, this.itemsInput)
    : items = itemsInput.map(BigInt.from).toList();

  var inspectCount = 0;
  
  int _dispatch(BigInt x) => x % BigInt.from(dispatcher[0]) == BigInt.zero ? dispatcher[1] : dispatcher[2];

  void process() {
    items
      .map(inspect)
      .forEach((item) {
        monkeys[_dispatch(item)].items.add(item);
        inspectCount ++;
      });
    items.clear();
  }
}

final monkeys = 
[
  MonkeyProcessor((x) => x*BigInt.from(3), const [2, 1, 4], [66, 59, 64, 51]),
  MonkeyProcessor((x) => x*BigInt.from(19), const [7, 3, 5], [67, 61]),
  MonkeyProcessor((x) => x+BigInt.from(2), const [11, 4, 0], [86, 93, 80, 70, 71, 81, 56]),
  MonkeyProcessor((x) => x*x, const [19, 7, 6], [94]),
  MonkeyProcessor((x) => x+BigInt.from(8), const [3, 5, 1], [71, 92, 64]),
  MonkeyProcessor((x) => x+BigInt.from(6), const [5, 3, 6], [58, 81, 92, 75, 56]),
  MonkeyProcessor((x) => x+BigInt.from(7), const [17, 7, 2], [82, 98, 77, 94, 86, 81]),
  MonkeyProcessor((x) => x+BigInt.from(4), const [13, 2, 0], [54, 95, 70, 93, 88, 93, 63, 50]),
];

// final monkeys = 
// [
//   MonkeyProcessor((x) => x*BigInt.from(19), const [23, 2, 3], [79, 98]),
//   MonkeyProcessor((x) => x+BigInt.from(6), const [19, 2, 0], [54, 65, 75, 74]),
//   MonkeyProcessor((x) => x*x, const [13, 1, 3], [79, 60, 97]),
//   MonkeyProcessor((x) => x+BigInt.from(3), const [17, 0, 1], [74]),
// ];

void main() {
  for (int _ = 0; _ < 10000; _ ++) {
    monkeys.forEach((monkey) => monkey.process());
  }

  final res = monkeys.map((monkey) => monkey.inspectCount).toList();
  res.sort((a, b) => b - a);
  print(res[0] * res[1]);
}
