classdef experiment

    properties (GetAccess=public)
	fname
	legend
	style
	fcolor
	msize
	lwidth

	n
	t
    end

    methods
	function obj = experiment(fname, legend, style, fcolor, msize, lwidth)
	    obj.legend = legend;
	    obj.style  = style;
	    obj.fcolor = fcolor;

	    if nargin >= 5
		obj.msize  = msize;
	    else
		obj.msize = 5;
	    end

	    if nargin >= 6
		obj.lwidth = lwidth;
	    else
		obj.lwidth = 1;
	    end

	    data = load([fname '.dat']);

	    obj.n = unique(data(:,1))';
	    obj.t = [];
	    for i = obj.n
		I = find(data(:,1) == i);
		time = median(data(I,2));
		obj.t = [obj.t time];
	    end
	end

	function h = loglog(obj, data)
	    if nargin >= 2
		h = loglog(obj.n, data, obj.style,     ...
		    'MarkerSize',      obj.msize,  ...
		    'Color',           obj.fcolor, ...
		    'MarkerFaceColor', 'w', ...
		    'LineWidth',       obj.lwidth);
	    else
		h = loglog(obj.n, obj.t, obj.style,    ...
		    'MarkerSize',      obj.msize,  ...
		    'Color',           obj.fcolor, ...
		    'MarkerFaceColor', 'w', ...
		    'LineWidth',       obj.lwidth);
	    end
	end

	function h = semilogx(obj, data)
	    if nargin >= 2
		h = semilogx(obj.n, data, obj.style,   ...
		    'MarkerSize',      obj.msize,  ...
		    'Color',           obj.fcolor, ...
		    'MarkerFaceColor', 'w', ...
		    'LineWidth',       obj.lwidth);
	    else
		h = semilogx(obj.n, obj.t, obj.style,  ...
		    'MarkerSize',      obj.msize,  ...
		    'Color',           obj.fcolor, ...
		    'MarkerFaceColor', 'w', ...
		    'LineWidth',       obj.lwidth);
	    end
	end
    end
end
