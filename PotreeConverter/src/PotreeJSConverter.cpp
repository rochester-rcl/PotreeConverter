#include <stdio.h>
#include <iostream>
#include <emscripten.h>
#include "PotreeJSConverter.hpp"
#include "PotreeConverter.h"


PotreeJSConverter::PotreeJSConverter(PotreeArguments arguments, bool runtime)
  : ptConverter(arguments.executablePath, arguments.outdir, arguments.source) {

  nodeRuntime = runtime;
  if (nodeRuntime) {
    // Set virtual file system root to cwd
    EM_ASM(
      FS.mkdir('/working');
      FS.mount(NODEFS, { root: '.'}, '/working');
    );
  }

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
