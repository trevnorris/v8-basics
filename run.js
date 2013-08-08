var basics = require('./build/Release/basics');

var arrIndex = { 0: true };
var arrName = { sym: true };

var iter = 1e7;
var t = process.hrtime();

for (var i = 0; i < iter; i++) {
  //basics.getPropIndex(arrIndex);
  //basics.getPropName(arrName);

  //basics.setPropIndex({});
  //basics.setPropName({});
}

t = process.hrtime(t);

console.log(((t[0] * 1e9 + t[1]) / iter).toFixed(1) + ' ns/op');
console.log((t[0] + t[1] / 1e9) + ' sec.');


function JSNew() {
  this.domain = process.domain;
}
/* */
