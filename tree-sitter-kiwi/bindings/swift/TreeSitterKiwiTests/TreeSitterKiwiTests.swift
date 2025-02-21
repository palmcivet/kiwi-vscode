import XCTest
import SwiftTreeSitter
import TreeSitterKiwi

final class TreeSitterKiwiTests: XCTestCase {
    func testCanLoadGrammar() throws {
        let parser = Parser()
        let language = Language(language: tree_sitter_kiwi())
        XCTAssertNoThrow(try parser.setLanguage(language),
                         "Error loading Kiwi grammar")
    }
}
