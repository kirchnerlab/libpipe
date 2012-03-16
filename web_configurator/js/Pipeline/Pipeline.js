/**
 * @author David Sichau
 */
function Pipeline(pipelineFile) {
	//private stuff
	var pipelineFile_ = pipelineFile;
	var pipeline;

	//public stuff
	// parse the input file and prints it to id
	this.loadJSON = function() {
		console.debug("load JSON and parse the JSON");
		$.getJSON(pipelineFile_, function(json) {
			pipeline = json;
		});
	};
	//prints the JSON in div with id=id
	this.printJSON = function(id) {
		console.debug("generate html json with input forms");
		var html = "";
		html += '<div id="' + id + '"><button id="exportPipeline">Export</button><button id="addPipeline">Add new Pipeline Object</button><button id="delPipeline">Remove Pipeline Object</button><ul>';
		$.each(pipeline, function() {
			$.each(this, function(id) {
				html += '<li id="' + id + '"><ul  type="none">';
				$.each(this, function(index, value) {
					html += '<li>' + index + ": " + value + '</li>';
				});
				html += '</ul></li>';
			});
		});
		html += '</ul></div>';
		return html;
	};
	// generate a txt output of JSON to copy in your config file
	this.generateJSONtxt = function(id) {
		console.debug("generate text json");
		var html = "";
		$.each(pipeline, function(root) {
			html += '<div id="' + id + '"> {<br />"' + root + '": [ <ul type="none">';
			$.each(this, function(id) {
				html += '{';
				$.each(this, function(index, value) {
					html += '<li>"' + index + '": "' + value + '",</li>';
				});
				html = html.substring(0, html.length - 6);
				html += '</li>},';
			});
			html = html.substring(0, html.length - 1);
			html += '</ul>] <br /> }</div>';
		});
		return html;
	}

	this.getJSON = function() {
		return pipeline;
	}

	this.addPipeline = function(filterName, requestType, requestRank, makeTrace) {
		console.debug("new Filter added");
		$.each(pipeline, function(root, val) {
			pipeline[root][val.length] = {
				filterName : filterName,
				requestType : requestType,
				requestRank : requestRank,
				makeTrace : makeTrace
			};
		});
	}

	this.delPipeline = function(pipelineId) {
		console.debug("new Parameter added");
		$.each(pipeline, function(root, value) {
			value = jQuery.grep(value, function(temp, temp2) {
				return temp2 != pipelineId;
			});
			pipeline[root] = value;
			console.debug("Parameter deleted");
		});
	}
	// open dialog with the new connection file
	$('#exportPipeline').live('click', function() {
		$("#export_layer").remove();
		var html = completeFilter.pipeline.generateJSONtxt("export_layer");
		$(html).appendTo('body');
		$(function() {
			$("#export_layer").dialog({
				width : 550,
				modal : true
			});
		});
	});
}