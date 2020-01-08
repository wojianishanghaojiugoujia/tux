(function () {
    function A() { }

    A.prototype.f = function () {
        console.log('fff', __dirname)
    }

    return A
})()
