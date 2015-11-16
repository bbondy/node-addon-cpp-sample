// hello.js
var addon = require('./build/Release/hasher');

console.log(addon.hash('brian'));
console.log(addon.sum(3,7));
