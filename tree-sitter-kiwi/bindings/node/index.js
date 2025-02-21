const root = require('node:path').join(__dirname, '..', '..');
const process = require('node:process');

module.exports
  = typeof process.versions.bun === 'string'
    // Support `bun build --compile` by being statically analyzable enough to find the .node file at build-time
    ? require(`../../prebuilds/${process.platform}-${process.arch}/tree-sitter-kiwi.node`)
    : require('node-gyp-build')(root);

try {
  module.exports.nodeTypeInfo = require('../../src/node-types.json');
}
// eslint-disable-next-line unused-imports/no-unused-vars
catch (error) {}
