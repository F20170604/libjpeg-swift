import libjpeg

struct libjpeg_swift {
    var text = "Hello, World!"
}

func tryHello(){
  let tjhandle = tjInitCompress()
  if(tjhandle != nil) {
    print("Hello")
  }
}
