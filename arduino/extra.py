Import("env")

def on_upload(source, target, env):
    print("\n----- Starting Serial Monitor -----")
    env.Execute("pio device monitor -b 115200")

env.AddPostAction("upload", on_upload)