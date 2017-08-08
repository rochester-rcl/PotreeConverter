
var Module = {};
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
