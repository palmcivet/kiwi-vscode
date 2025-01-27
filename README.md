# Kiwi VSCode

Better support for the Kiwi message format in Visual Studio Code.

Forked from [connorskees/kiwi-lsp](https://github.com/connorskees/kiwi-lsp), which published on [VSCode Marketplace](https://marketplace.visualstudio.com/items?itemName=connorskees.kiwi-lsp), identified by `connorskees.kiwi-lsp`.

## Features

The following features are provided by the original plugin:

- Syntax highlighting using TextMate syntax
- Basic language configuration (comments, brackets, etc)
- Jump-to-definition, autocomplete, find-all-references, codelens support, basic docs on hover, and minor linting
- Quick actions for changing incorrect casing and generating the next available id for messages (especially useful for large messages with hundreds of fields)

Building on this, the following features have been added:

- Support for splitting `.kiwi` files based on business requirements, with proper dependency recognition via the `kiwi-vscode.includeFiles` setting

## Example

See the fixture/ folder.

The dependencies are as follows: `package/derived.kiwi` depends on `enum.kiwi`, `package/base-1.kiwi`, and `package/base-2.kiwi`. `derived.kiwi` uses types from `enum.kiwi`, and during parsing, `enum.kiwi` is prepended to `derived.kiwi`.

```
enum.kiwi              \
package/base-1.kiwi ----> package/derived.kiwi
package/base-2.kiwi    /
```

By configuring the `kiwi-vscode.includeFiles`, dependencies can be added in order during parsing.

## Credits

- [Cursor](https://www.cursor.com/)
- [Visual Studio Code](https://code.visualstudio.com/)

## License

MIT
