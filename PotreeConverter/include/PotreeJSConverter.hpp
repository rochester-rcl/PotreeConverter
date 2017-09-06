// Potree Converter Emscripten Bindings

#include <stdio.h>
#include <stdlib.h>
#include "AABB.h"
#include "PotreeConverter.h"
#include "PotreeException.h"
#include <emscripten/bind.h>

using namespace emscripten;

using namespace std;

using Potree::PotreeConverter;
using Potree::StoreOption;
using Potree::ConversionQuality;
using Potree::OutputFormat;

struct PotreeArguments {
	StoreOption storeOption = StoreOption::ABORT_IF_EXISTS;
	vector<string> source;
	string outdir;
	float spacing;
	int levels;
	string format;
	double scale;
	int diagonalFraction;
	OutputFormat outFormat;
	vector<double> colorRange;
	vector<double> intensityRange;
	vector<string> outputAttributes;
	bool generatePage;
	vector<double> aabbValues;
	string pageName;
	string projection;
	bool sourceListingOnly;
	string listOfFiles;
	ConversionQuality conversionQuality;
	string conversionQualityString;
	string title;
	string description;
	bool edlEnabled;
	bool showSkybox;
	string material;
  string executablePath;
};

class PotreeJSConverter {

	private:
		 PotreeConverter ptConverter;

  public:
     // Can add all of the other options later + set this up as a worker
     PotreeJSConverter(PotreeArguments arguments);
		 vector<int> totalPoints;
		 long pointsProcessed;

		 vector<int> getTotalPoints() const { return ptConverter.totalPoints; }
		 void setTotalPoints(vector<int> points) { totalPoints = points; }

		 long getPointsProcessed() const { return ptConverter.pointCount; }
		 void setPointsProcessed(long points) { pointsProcessed = points; }
		 void convert();
		 void compress(string srcPath, string zipName);

};

EMSCRIPTEN_BINDINGS(potree_js_converter) {

	register_vector<string>("VectorString");
	register_vector<double>("VectorDouble");
	register_vector<int>("VectorInt");

	enum_<StoreOption>("StoreOption")
		.value("ABORT_IF_EXISTS", StoreOption::ABORT_IF_EXISTS)
		.value("OVERWRITE", StoreOption::OVERWRITE)
		.value("INCREMENTAL", StoreOption::INCREMENTAL);

	enum_<OutputFormat>("OutputFormat")
		.value("BINARY", OutputFormat::BINARY)
		.value("LAS", OutputFormat::LAS)
		.value("LAZ", OutputFormat::LAZ);

	enum_<ConversionQuality>("ConversionQuality")
		.value("FAST", ConversionQuality::FAST)
		.value("DEFAULT", ConversionQuality::DEFAULT)
		.value("NICE", ConversionQuality::NICE);

  class_<PotreeJSConverter>("PotreeJSConverter")
  	.constructor<PotreeArguments>()
		.function("convert", &PotreeJSConverter::convert)
		.function("compress", &PotreeJSConverter::compress)
		.property("totalPoints", &PotreeJSConverter::getTotalPoints, &PotreeJSConverter::setTotalPoints)
		.property("pointsProcessed", &PotreeJSConverter::getPointsProcessed, &PotreeJSConverter::setPointsProcessed);

	value_object<PotreeArguments>("PotreeArguments")
		.field("source", &PotreeArguments::source)
		.field("outdir", &PotreeArguments::outdir)
		.field("spacing", &PotreeArguments::spacing)
		.field("levels", &PotreeArguments::levels)
		.field("format", &PotreeArguments::format)
		.field("scale", &PotreeArguments::scale)
		.field("diagonalFraction", &PotreeArguments::diagonalFraction)
		.field("outFormat", &PotreeArguments::outFormat)
		.field("colorRange", &PotreeArguments::colorRange)
		.field("intensityRange", &PotreeArguments::intensityRange)
		.field("outputAttributes", &PotreeArguments::outputAttributes)
		.field("generatePage", &PotreeArguments::generatePage)
		.field("aabbValues", &PotreeArguments::aabbValues)
		.field("pageName", &PotreeArguments::pageName)
		.field("projection", &PotreeArguments::projection)
		.field("sourceListingOnly", &PotreeArguments::sourceListingOnly)
		.field("listOfFiles", &PotreeArguments::listOfFiles)
		.field("conversionQuality", &PotreeArguments::conversionQuality)
		.field("conversionQualityString", &PotreeArguments::conversionQualityString)
		.field("title", &PotreeArguments::title)
		.field("description", &PotreeArguments::description)
		.field("edlEnabled", &PotreeArguments::edlEnabled)
		.field("showSkybox", &PotreeArguments::showSkybox)
		.field("material", &PotreeArguments::material)
		.field("executablePath", &PotreeArguments::executablePath);
}
