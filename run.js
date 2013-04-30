var basics = require('./build/Release/basics');

var md5 = basics.md5;

console.log(md5('abc'));
process.exit();

var iter = 1e7;

var time = process.hrtime();
for (var i = 0; i < iter; i++) {
  md5(i + '');
}
time = process.hrtime(time);

console.log((time[0] * 1e9 + time[1]) / iter);
