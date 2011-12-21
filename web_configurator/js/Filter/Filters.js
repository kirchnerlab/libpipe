/**
 * @author David Sichau
 */
function Filters(filtersFile) {
	//private stuff
	var filterFile = filtersFile;
	var filters;

	//public stuff
	// parse the input file and prints it to id
	this.loadJSON = function() {
		console.debug("load JSON and parse the JSON");
		$.getJSON(filterFile, function(json) {
			filters = json;
		});
	};
	//prints the JSON in div with id=id
	this.printJSON = function(id) {
		console.debug("generate html json with input forms");
		var html = "";
		html += '<div id="' + id + '"><button id="exportFilters">Export</button><button id="addFilter">Add new Filter</button><button id="delFilter">Remove Filter</button><ul>';
		$.each(filters, function() {
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
		$.each(filters, function(root) {
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
		return filters;
	}

	this.addFilter = function(filterIdentifier, paramIdentifier, param) {
		console.debug("new Filter added");
		$.each(filters, function(root, val) {
			filters[root][val.length] = {
				filterIdentifier : filterIdentifier,
				paramIdentifier : paramIdentifier,
				param : param
			};
		});
	}

	this.delFilter = function(filterId) {
		$.each(filters, function(root, value) {
			value = jQuery.grep(value, function(temp, temp2) {
				return temp2 != filterId;
			});
			filters[root] = value;
			console.debug("Parameter deleted");
		});
	}
	// open dialog with the new filter file
	$('#exportFilters').live('click', function() {
		$("#export_layer").remove();
		var html = completeFilter.filters.generateJSONtxt("export_layer");
		$(html).appendTo('body');
		$(function() {
			$("#export_layer").dialog({
				width : 550,
				modal : true
			});
		});
	});
}