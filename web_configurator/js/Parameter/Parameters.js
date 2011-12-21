/**
 * @author David Sichau
 */
function Parameters(parametersFile) {
	//private stuff
	var paramFile = parametersFile;
	var params;

	//public stuff
	// parse the input file and prints it to id
	this.loadJSON = function() {
		console.debug("load JSON and parse the JSON");
		$.getJSON(paramFile, function(json) {
			params = json;
		});
	};
	//prints the JSON in div with id=id
	this.printJSON = function(id) {
		console.debug("generate html json with input forms");

		var html = "";
		html += '<div id="' + id + '"><button id="exportParameters">Export</button><button id="addParam">Add new Parameter</button><button id="delParam">Remove Parameter</button><ul>';

		$.each(params, function() {
			$.each(this, function(id) {
				html += '<li id="' + id + '"><ul  type="none">';
				$.each(this, function(index, value) {
					if($.isArray(value)) {
						html += '<li>' + index + ': <ul>';
						$.each(this, function(id2) {
							$.each(this, function(index2, value2) {
								if(index2 == 'param') {
									html += ' ' + index2 + ': <input id="' + id + '" type="text" value="' + value2 + '" /></li>';
								} else {
									html += '<li id="' + id2 + '">' + index2 + ': ' + value2 + "<br />";
								}
							});
						});
						html += '</ul></li>'
					} else {
						html += '<li>' + index + ": " + value + '</li>';
					}
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
		$.each(params, function(root) {
			html += '<div id="' + id + '"> {<br />"' + root + '": [ <ul type="none">';
			$.each(this, function(id) {
				html += '{';
				$.each(this, function(index, value) {
					if($.isArray(value)) {
						//if no parameters are given
						if(value.length == 0) {
							html += '<li>"' + index + '":[ ]</li>';
						} else {
							html += '<li>"' + index + '":[ <ul type="none">';
							$.each(this, function(id2) {
								html += '<li>{<ul type="none">';
								$.each(this, function(index2, value2) {
									if(index2 == 'param') {
										html += ' <li>"' + index2 + '": "' + value2 + '"</li>';
									} else {
										html += '<li>"' + index2 + '":" ' + value2 + '",</li>';
									}
								});
								html += '</ul>}</li>,';
							});
							html = html.substring(0, html.length - 1);
							html += ']</ul></li>'
						}
					} else {
						html += '<li>"' + index + '": "' + value + '",</li>';
					}
				});
				html += '},';
			});
			html = html.substring(0, html.length - 1);
			html += '</ul>] <br /> }</div>';
		});
		return html;
	}

	this.getJSON = function() {
		return params;
	}
	this.setParam = function(key, paramIdentifier, newValue) {
		console.debug("Parameter param changed called");
		$.each(params, function(root) {
			$.each(this, function(id) {
				if(id == key) {
					$.each(this, function(index, value) {
						if($.isArray(value)) {
							$.each(this, function(id2) {
								if(id2 == paramIdentifier) {
									$.each(this, function(index2, value2) {
										if(index2 == 'param' && value2 != newValue) {
											console.debug("Parameter param changed from: " + value2 + " to: " + newValue);
											params[root][id][index][id2][index2] = newValue;
										}
									});
								}

							});
						}
					});
				}
			});
		});
	}
	// add a new parameter to the parameter list.
	this.addParams = function(filterIdentifier, paramIdentifier, param) {
		console.debug("new Parameter added");
		var isInList = false;
		$.each(params, function(root) {
			$.each(this, function(id) {
				$.each(this, function(index, value) {
					if($.isArray(value) && params[root][id].filterIdentifier == filterIdentifier) {
						isInList = true;
						console.debug("New Parameter added to filter: " + filterIdentifier);
						params[root][id][index][value.length] = {
							paramIdentifier : paramIdentifier,
							param : param
						}

					}

				});
			});
		});
		// the filter did not exist before.
		if(!isInList) {
			$.each(params, function(root, val) {
				console.debug("New Parameter added to new filter: " + filterIdentifier);
				params[root][val.length] = {
					filterIdentifier : filterIdentifier,
					parameters : [{
						paramIdentifier : paramIdentifier,
						param : param
					}]
				}
			});
		}
	}
	// delete a parameter.
	this.delParams = function(filterId, paramId) {
		$.each(params, function(root) {
			$.each(this, function(id) {
				if(id == filterId) {
					$.each(this, function(index, value) {
						if($.isArray(value)) {
							value = jQuery.grep(value, function(temp, temp2) {
								return temp2 != paramId;
							});
							params[root][id][index] = value;
							console.debug("Parameter deleted");

						}

					});
				}

			});
		});
	}
	// checks the parameter input for changed values and renews the div showParams
	$("#showParams :input:text").live('change', function() {
		var value = $(this).val();
		var currentId = $(this).attr('id');
		var paramIdentifier = $(this).parent().attr('id');
		completeFilter.params.setParam(currentId, paramIdentifier, value);
		//renew the div
		var html_ = completeFilter.params.printJSON("showParams")
		$('#showParams').html(html_);
	}).change();

	// open dialog with the new parameter file
	$('#exportParameters').live('click', function() {
		$("#export_layer").remove();
		var html = completeFilter.params.generateJSONtxt("export_layer");
		$(html).appendTo('body');
		$(function() {
			$("#export_layer").dialog({
				width : 550,
				modal : true,
				buttons : {
					Ok : function() {
						$(this).dialog("close");
					}
				}
			});
		});
	});
}