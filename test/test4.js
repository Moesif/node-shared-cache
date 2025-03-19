const assert = require("assert");
const cache = require("../index.js");

// Clean up any existing shared memory
try {
  cache.release("test");
} catch (e) {
  // Ignore errors if shared memory doesn't exist
}

let obj = new cache.Cache("test", 100 * 1024 * 1024);

console.time("Node test: ");

for (let i = 0; i <= 1200; i++) {
  obj["test" + i] = i;
}

for (let i = 0; i <= 1200; i++) {
  assert.strictEqual(obj["test" + i], i);
}

console.timeEnd("Node test: ");

// Clean up after test
try {
  cache.release("test");
} catch (e) {
  // Ignore errors if shared memory doesn't exist
}

// console.log("==== Dump ====");
// console.log(cache.dump(obj));
