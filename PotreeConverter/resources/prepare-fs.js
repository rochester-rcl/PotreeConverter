Module['mountNODEFS'] = function(virtualRoot) {
  FS.mkdir(virtualRoot);
  FS.mount(NODEFS, { root: '.' }, virtualRoot);
};

Module['mountWORKERFS'] = function(virtualRoot, file) {
  FS.mkdir(virtualRoot);
  FS.mount(WORKERFS, {
    files: [file],
  }, virtualRoot );
};

Module['ls'] = function(path) {
  return FS.readdir(path);
}

Module['onRuntimeInitialized'] = function() {
  return true;
}
