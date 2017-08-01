const pt = require('./PotreeConverter');

const StoreOptions = pt.StoreOption;
const ConversionQuality = pt.ConversionQuality;
const OutputFormat = pt.OutputFormat;

const source = new pt.VectorString();
source.push_back('test');

const colorRange = new pt.VectorDouble();
colorRange.push_back(255.0);

const intensityRange = new pt.VectorDouble();
intensityRange.push_back(1.0);

const outputAttributes = new pt.VectorString();
outputAttributes.push_back('test');

const aabbValues = new pt.VectorDouble();
aabbValues.push_back(100.0);

const args = {
  storeOption: StoreOptions.ABORT_IF_EXISTS,
	source: source,
  outdir: 'test',
  spacing: 1.0,
  levels: 1,
  format: 'test',
  scale: 1.0,
	diagonalFraction: 1,
  outFormat: OutputFormat.BINARY,
	colorRange: colorRange,
  intensityRange: intensityRange,
  outputAttributes: outputAttributes,
  generatePage: false,
  aabbValues: aabbValues,
	pageName: '',
	projection: '',
	sourceListingOnly: false,
	listOfFiles: '',
	conversionQuality: ConversionQuality.DEFAULT,
	conversionQualityString: "",
	title: "PotreeViewer",
	description: "",
	edlEnabled: false,
	showSkybox: false,
	material: "RGB",
  executablePath: 'test',
}

var converter = new pt.PotreeJSConverter(args.executablePath, args.outdir, args.source, args);
