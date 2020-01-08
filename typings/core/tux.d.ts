declare const Tux = {
    realpath(path: String): String { },
    dirname(path: String): String { },
    glob(pattern: String): Array<String> { },
    sleep(microtimes: Number) { },
    exit(code: Number = 0) { },
    cwd(): String { },
    entryPath(): String { },
}