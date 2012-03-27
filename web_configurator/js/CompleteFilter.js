/**
 * @author David Sichau
 */
function CompleteFilter() {

	this.params
	this.filters
	this.connections
	this.pipeline
	
	this.loadEmptyData = function() {

		var urlParams = "inputFiles/Parameters.txt" ;
		var urlFilter = "inputFiles/Filter.txt";
		var urlConnection = "inputFiles/Connection.txt";
		var urlPipeline = "inputFiles/Pipeline.txt";
		this.params = new Parameters(urlParams);
		this.filters = new Filters(urlFilter);
		this.connections = new Connections(urlConnection);
		this.pipeline = new Pipeline(urlPipeline);
		//to synchonise the calls
		$.ajaxSetup({
			async : false
		});
		this.params.loadJSON();
		$.ajaxSetup({
			async : false
		});
		this.filters.loadJSON();
		$.ajaxSetup({
			async : false
		});
		this.connections.loadJSON();
		$.ajaxSetup({
			async : false
		});
		this.pipeline.loadJSON();

		$("#loadFiles").slideUp();
	}	
	
	
	
	this.loadData = function() {
		alert($(":input[name=fileParameter]").val())
		var urlParams = $(":input[name=fileParameter]").val();
		var urlFilter = $(":input[name=fileFilter]").val();
		var urlConnection = $(":input[name=fileConnection]").val();
		var urlPipeline = $(":input[name=filePipeline]").val();
		this.params = new Parameters(urlParams);
		this.filters = new Filters(urlFilter);
		this.connections = new Connections(urlConnection);
		this.pipeline = new Pipeline(urlPipeline);
		//to synchonise the calls
		$.ajaxSetup({
			async : false
		});
		this.params.loadJSON();
		$.ajaxSetup({
			async : false
		});
		this.filters.loadJSON();
		$.ajaxSetup({
			async : false
		});
		this.connections.loadJSON();
		$.ajaxSetup({
			async : false
		});
		this.pipeline.loadJSON();

		$("#loadFiles").slideUp();
	}

	this.generateTabs = function() {

		var html = '';
		html += '<div id="tabs"><ul>';
		html += '<li><a href="#showParams">Parameters</a></li>';
		html += '<li><a href="#showFilters">Filters</a></li>';
		html += '<li><a href="#showPipeline">Pipeline</a></li>';
		html += '<li><a href="#showConnections">Connections</a></li>';
		html += '</ul>';
		html += this.params.printJSON("showParams");
		html += this.filters.printJSON("showFilters");
		html += this.pipeline.printJSON("showPipeline");
		html += this.connections.printJSON("showConnections");
		html += '</div>';
		return html;

	}

}