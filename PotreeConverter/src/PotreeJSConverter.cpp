#include <stdio.h>
#include <iostream>
#include <emscripten.h>
#include <zip.h>
#include <boost/filesystem.hpp>
#include "PotreeJSConverter.hpp"
#include "PotreeConverter.h"
#include "PotreeException.h"

using namespace std;
using namespace boost::filesystem;

PotreeJSConverter::PotreeJSConverter(PotreeArguments arguments)
  : ptConverter(arguments.executablePath, arguments.outdir, arguments.source) {

  ptConverter.spacing = arguments.spacing;
	ptConverter.diagonalFraction = arguments.diagonalFraction;
	ptConverter.maxDepth = arguments.levels;
	ptConverter.format = arguments.format;
	ptConverter.colorRange = arguments.colorRange;
	ptConverter.intensityRange = arguments.intensityRange;
	ptConverter.scale = arguments.scale;
	ptConverter.outputFormat = arguments.outFormat;
	ptConverter.outputAttributes = arguments.outputAttributes;
	ptConverter.aabbValues = arguments.aabbValues;
	ptConverter.pageName = arguments.pageName;
	ptConverter.storeOption = arguments.storeOption;
	ptConverter.projection = arguments.projection;
	ptConverter.sourceListingOnly = arguments.sourceListingOnly;
	ptConverter.quality = arguments.conversionQuality;
	ptConverter.title = arguments.title;
	ptConverter.description = arguments.description;
	ptConverter.edlEnabled = arguments.edlEnabled;
	ptConverter.material = arguments.material;
	ptConverter.showSkybox = arguments.showSkybox;

};

void PotreeJSConverter::convert() {
    ptConverter.convert();
}

void PotreeJSConverter::compress(string srcPath, string zipName) {
  int err = 0;
  if (exists(srcPath) && is_directory(srcPath)) {
    recursive_directory_iterator end;
    zip *zipArchive = zip_open(zipName.c_str(), ZIP_CREATE, &err);
    for (recursive_directory_iterator dirs(srcPath); dirs != end; ++dirs) {
      const char* currentPath = dirs->path().string().c_str();
      if (!is_directory(currentPath)) {
        zip_source *sourceFile = zip_source_file(zipArchive, currentPath, 0, 2);
        zip_uint64_t added = zip_file_add(zipArchive, currentPath, sourceFile, ZIP_FL_OVERWRITE);
      }
    }
    int closeError = zip_close(zipArchive);
    if (err != 0 || zipArchive == NULL) {
      cout << zip_strerror(zipArchive) << endl;
    }
    if (closeError != 0) {
      cout << zip_strerror(zipArchive) << endl;
    }
    if (exists(zipName)) {
      permissions(zipName, owner_all|group_read|group_exe|others_read|others_exe);
    }
  }
}
