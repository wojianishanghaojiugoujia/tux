declare class Mat {
    static read(path: String): Mat
    static make(data: String | Buffer, fmt: String = "base64"): Mat
    static wait_key(delay: Number = 0): Number

    constructor(p: pointer) { }
    release() { }
    crop(rectLike: Object): Mat { }
    find(tplMat: Mat, ...rectLikes?: Array<Object>): Array<TplMatchResult> { }
    show(title: String = "") { }
}