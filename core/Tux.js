(function () {
    var TUX = {}

    TUX.realpath = function (path) {
        return realpath.apply(null, Array.prototype.slice.call(arguments))
    }

    TUX.dirname = function (path) {
        return dirname.apply(null, Array.prototype.slice.call(arguments))
    }

    TUX.entryPath = function () {
        return entry_path.apply(null, Array.prototype.slice.call(arguments))
    }

    TUX.cwd = function () {
        return cwd.apply(null, Array.prototype.slice.call(arguments))
    }

    TUX.glob = function (pattern) {
        return glob.apply(null, Array.prototype.slice.call(arguments))
    }

    TUX.sleep = function (microtimes) {
        return sleep.apply(null, Array.prototype.slice.call(arguments))
    }

    TUX.exit = function (code) {
        return exit.apply(null, Array.prototype.slice.call(arguments))
    }

    return TUX
})()