import XCTest

#if !canImport(ObjectiveC)
public func allTests() -> [XCTestCaseEntry] {
    return [
        testCase(libjpeg_swiftTests.allTests),
    ]
}
#endif
