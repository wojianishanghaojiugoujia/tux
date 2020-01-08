(function () {
    function Win(h) {
        this.h = h
    }

    Win.fromMouse = function () {
        return new Win(win_from_mouse())
    }

    Win.waitKey = function (delay) {
        return wait_key.apply(null, Array.prototype.slice.call(arguments))
    }

    Win.prototype.position = function (clientOnly) {
        return win_position.apply(null, [this.h].concat(Array.prototype.slice.call(arguments)))
    }

    Win.prototype.setPosition = function (pointLike, clientOnly) {
        return win_set_position.apply(null, [this.h].concat(Array.prototype.slice.call(arguments)))
    }

    Win.prototype.size = function (clientOnly) {
        return win_size.apply(null, [this.h].concat(Array.prototype.slice.call(arguments)))
    }

    Win.prototype.resize = function (sizeLike, clientOnly) {
        return win_resize.apply(null, [this.h].concat(Array.prototype.slice.call(arguments)))
    }

    Win.prototype.rect = function (clientOnly) {
        return win_rect.apply(null, [this.h].concat(Array.prototype.slice.call(arguments)))
    }

    Win.prototype.capture = function (rectLike, clientOnly) {
        return new Mat(win_capture.apply(null, [this.h].concat(Array.prototype.slice.call(arguments))))
    }

    Win.prototype.active = function () {
        return win_active.apply(null, [this.h].concat(Array.prototype.slice.call(arguments)))
    }

    Win.prototype.zorder = function (winOrOrder) {
        var o = winOrOrder instanceof Win ? winOrOrder.h : winOrOrder
        return win_zorder(this.h, o)
    }

    Win.prototype.show = function (cmd) {
        return win_show.apply(null, [this.h].concat(Array.prototype.slice.call(arguments)))
    }

    Win.prototype.mouse_scroll = function (pointLike, step) {
        return mouse_scroll.apply(null, [this.h].concat(Array.prototype.slice.call(arguments)))
    }

    Win.prototype.mouse_click = function (pointLike, btn) {
        return mouse_click.apply(null, [this.h].concat(Array.prototype.slice.call(arguments)))
    }

    Win.prototype.mouse_dbclick = function (pointLike, btn) {
        return mouse_dbclick.apply(null, [this.h].concat(Array.prototype.slice.call(arguments)))
    }

    Win.prototype.mouse_move = function (pointLike, btn) {
        return mouse_move.apply(null, [this.h].concat(Array.prototype.slice.call(arguments)))
    }

    Win.prototype.mouse_up = function (pointLike, btn) {
        return mouse_up.apply(null, [this.h].concat(Array.prototype.slice.call(arguments)))
    }

    Win.prototype.mouse_down = function (pointLike, btn) {
        return mouse_down.apply(null, [this.h].concat(Array.prototype.slice.call(arguments)))
    }

    return Win
})()
