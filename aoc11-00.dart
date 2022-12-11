class MonkeyProcessor {
  final int Function(int) inspect;
  final List<int> dispatcher;
  final List<int> items;
  MonkeyProcessor(this.inspect, this.dispatcher, this.items);

  var inspectCount = 0;
  
  int _dispatch(int x) => x % dispatcher[0] == 0 ? dispatcher[1] : dispatcher[2];

  void process() {
    items
      .map((x) => inspect(x) ~/ 3)
      .forEach((item) {
        monkeys[_dispatch(item)].items.add(item);
        inspectCount ++;
      });
    items.clear();
  }
}

final monkeys = 
[
  MonkeyProcessor((x) => x*3, const [2, 1, 4], [66, 59, 64, 51]),
  MonkeyProcessor((x) => x*19, const [7, 3, 5], [67, 61]),
  MonkeyProcessor((x) => x+2, const [11, 4, 0], [86, 93, 80, 70, 71, 81, 56]),
  MonkeyProcessor((x) => x*x, const [19, 7, 6], [94]),
  MonkeyProcessor((x) => x+8, const [3, 5, 1], [71, 92, 64]),
  MonkeyProcessor((x) => x+6, const [5, 3, 6], [58, 81, 92, 75, 56]),
  MonkeyProcessor((x) => x+7, const [17, 7, 2], [82, 98, 77, 94, 86, 81]),
  MonkeyProcessor((x) => x+4, const [13, 2, 0], [54, 95, 70, 93, 88, 93, 63, 50]),
];

// final monkeys = 
// [
//   MonkeyProcessor((x) => x*19, const [23, 2, 3], [79, 98]),
//   MonkeyProcessor((x) => x+6, const [19, 2, 0], [54, 65, 75, 74]),
//   MonkeyProcessor((x) => x*x, const [13, 1, 3], [79, 60, 97]),
//   MonkeyProcessor((x) => x+3, const [17, 0, 1], [74]),
// ];

void main() {
  for (int _ = 0; _ < 20; _ ++) {
    monkeys.forEach((monkey) => monkey.process());
  }

  final res = monkeys.map((monkey) => monkey.inspectCount).toList();
  res.sort((a, b) => b - a);
  print(res[0] * res[1]);
}
