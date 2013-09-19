var basics = require('./build/Release/basics');
var iter = 1e7;
var t;

var array = [];
var obj = {};
function noop() { }


basics.setup(noop, obj, array);

t = process.hrtime();

for (var i = 0; i < iter; i++) {
  basics.run();
  while (array.length > 0)
    array.pop()();
}

t = process.hrtime(t);


console.log((t[0] * 1e9 + t[1]) / iter);


function noop() { }
