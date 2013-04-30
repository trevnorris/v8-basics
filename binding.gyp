{
  "targets": [{
    "target_name": "basics",
    "sources": ["basics.cc"],
    "include_dirs": [ "<(node_root_dir)/deps/openssl/openssl/include" ],
    "conditions" : [
      ["target_arch=='ia32'", {
        "include_dirs": [ "<(node_root_dir)/deps/openssl/config/piii" ]
      }],
      ["target_arch=='x64'", {
        "include_dirs": [ "<(node_root_dir)/deps/openssl/config/k8" ]
      }],
      ["target_arch=='arm'", {
        "include_dirs": [ "<(node_root_dir)/deps/openssl/config/arm" ]
      }]
    ]
  }]
}
