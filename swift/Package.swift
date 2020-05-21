// swift-tools-version:5.2

import PackageDescription

let package = Package(
    name: "src",
    dependencies: [
        .package(url: "https://github.com/IBM-Swift/Kitura", from: "2.9.1")
    ],
    targets: [
        .target(
            name: "app",
            dependencies: ["Kitura"])
    ]
)
