declare class Win {
    static fromMouse(): Win
    static wait_key(delay: Number = 0): Number

    constructor(h: Number) { }
    position(clientOnly: Boolean = true): PointLike { }
    setPosition(pointLike: Object, clientOnly: Boolean = true) { }
    size(clientOnly: Boolean = true): SizeLike { }
    resize(sizeLike: Object, clientOnly: Boolean = true) { }
    rect(clientOnly: Boolean = true): RectLike { }
    capture(clientOnly: Boolean = true): Mat { }
    capture(rectLike: Object, clientOnly: Boolean = true): Mat { }
    active() { }
    zorder(winOrOrder: Win | Number) { }
    show(cmd: Number) { }

    mouse_scroll(pointLike: Object, step: Number = -120) { }
    mouse_click(pointLike: Object, btn: Number = -1) { }
    mouse_dbclick(pointLike: Object, btn: Number = -1) { }
    mouse_move(pointLike: Object, btn: Number = -1) { }
    mouse_up(pointLike: Object, btn: Number = -1) { }
    mouse_down(pointLike: Object, btn: Number = -1) { }
}