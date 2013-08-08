var basics = require('./build/Release/basics');

var arr = {0: true};

var iter = 1e7;
var t = process.hrtime();

for (var i = 0; i < iter; i++) {
  //new basics.BasicNew();
  //new basics.ExternalNew();
  //new basics.InternalNew();
  //new JSNew(process.domain);
  //basics.ArrayGet();
}

t = process.hrtime(t);

console.log(((t[0] * 1e9 + t[1]) / iter).toFixed(1) + ' ns/op');
console.log((t[0] + t[1] / 1e9) + ' sec.');


function JSNew() {
  this.domain = process.domain;
}
/* */
