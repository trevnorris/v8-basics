var basics = require('./build/Release/basics');
var iter = 1e7;
var t;

function noop() {
  return true;
}
basics.setup(noop);


t = process.hrtime();

for (var i = 0; i < iter; i++) {
  basics.run()();
}

t = process.hrtime(t);


console.log((t[0] * 1e9 + t[1]) / iter);
