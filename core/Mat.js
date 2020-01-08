(function () {
    function Mat(p) {
        this.p = p
        this.released = false
        Duktape.fin(this, function (mat) {
            mat.release()
        })
    }

    Mat.read = function (path) {
        return new Mat(mat_read.apply(null, Array.prototype.slice.call(arguments)))
    }

    Mat.make = function (data, fmt) {
        return new Mat(mat_make.apply(null, Array.prototype.slice.call(arguments)))
    }

    Mat.waitKey = function (delay) {
        return wait_key.apply(null, Array.prototype.slice.call(arguments))
    }

    Mat.prototype.show = function (title) {
        return mat_show.apply(null, [this.p].concat(Array.prototype.slice.call(arguments)))
    }

    Mat.prototype.find = function (tplMat, _) {
        return mat_find.apply(null, [this.p, tplMat.p].concat(Array.prototype.slice.call(arguments).slice(1)))
    }

    Mat.prototype.crop = function (rectLike) {
        return new Mat(mat_crop.apply(null, [this.p].concat(Array.prototype.slice.call(arguments))))
    }

    Mat.prototype.release = function () {
        if (!this.released) {
            try {
                console.debug("mat-release:" + this.p)
                mat_release.apply(null, [this.p])
                this.released = true
            } catch (e) {
                console.error('mat.release failed:' + e)
            }
        }
    }

    return Mat
})()
