import 'dart:convert';
import 'dart:io';
import 'dart:math';

bool eq(dynamic a, dynamic b) {
  final ret = equal(a, b);
  //print('equal $a == $b  ==> $ret');
  return ret;
}

bool equal(dynamic a, dynamic b) {
  if (a is int && b is int) return a == b;
  if (a is List && b is List) {
    if (a.length != b.length) return false;
    for (int i = 0; i < a.length; i ++) {
      if (!eq(a[i], b[i])) return false;
    }
    return true;
  }
  if (a is int) return eq([a], b);
  if (b is int) return eq(a, [b]);

  throw UnsupportedError('a :\n${a} \n b :\n${b}');
}

bool ls(dynamic a, dynamic b) {
  final ret = less(a, b);
  //print('less $a << $b ==> $ret');
  return ret;
}

bool less(dynamic a, dynamic b) {
  if (eq(a, b)) return false;
  if (a is int && b is int) return a < b;
  if (a is List && b is List) {
    if (a.isEmpty && b.isNotEmpty) return true;
    if (a.isNotEmpty && b.isEmpty) return false;
    final minLen = min(a.length, b.length);
    for (int i = 0; i < minLen; i ++) {
      if (ls(a[i], b[i])) return true;
      if (ls(b[i], a[i])) return false;
    }
    return a.length < b.length;
  }
  if (a is int) return ls([a], b);
  if (b is int) return ls(a, [b]);

  throw UnsupportedError('a :\n${a} \n b :\n${b}');
}

int cmp(List a, List b) {
  if (eq(a, b)) return 0;
  return ls(a, b) ? -1 : 1 ;
}

void main() async {
  String s = await File('13.in').readAsString();
  final inputs = s.split('\n\n');
  const a = [[6]];
  const b = [[2]];
  final list = <List>[a, b];
  for (int i = 0; i < inputs.length; i ++) {
    final ss = inputs[i].split('\n');
    list.add(jsonDecode(ss[0]) as List);
    list.add(jsonDecode(ss[1]) as List);
  }
  list.sort(cmp);
  print((list.indexOf(a) + 1) * (list.indexOf(b) + 1));
}