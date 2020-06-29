%current fft
function [p_new, bars_new] = currentfftv4(player,Y,FS,p_old, num_of_bars, cell_arr, bars)
    sampleNumber=get(player,'CurrentSample');
    timerVal=get(player,'TimerPeriod');
    maxY = 0.05;
    s1=Y(40 + floor(sampleNumber-((timerVal*FS)/2)):floor(sampleNumber+((timerVal*FS)/2)) - 40,1);
    % Modify the bounds above to make a power of 2
    n = length(s1);
    p = fft(s1);
    nUniquePts = ceil(n / 20);
    p = p(1:nUniquePts);
    p = abs(p);
    p = p/n;
    if length(bars) ~= length(p)
        disp('Instantiated bars');
        bars = zeros(length(p), num_of_bars + 2); % Only create empty matrix bars once
    end
    if ~ismatrix(p_old) % Used to fix p_old's first iteration
        p_old = zeros(length(p), 1);
    end
    for ii = 1:num_of_bars+1 % Decides which bars should be full, partial, or empty
        bars(p >= ii * maxY / num_of_bars, ii) = maxY / num_of_bars;
        cond = p > (ii - 1) * maxY / num_of_bars & p < ii * maxY / num_of_bars;
        bars(cond, ii) = p(cond) - (ii - 1) * maxY / num_of_bars;
    end
    pos_diff = p_old > p;
    bars(pos_diff ,num_of_bars + 1) = p_old(pos_diff) - p(pos_diff); % Set difference bar heights
    bars(:,num_of_bars + 2) = maxY/100; % Add white bar with set height
    h = bar(bars, 'stacked'); % Plot graph
    set(h, {'FaceColor'}, cell_arr); % Set colors
    set(h, 'BarWidth', 1);
    axis([-0.02 nUniquePts+1 0 maxY]); % Set axis bounds
    set(gca,'Color','k'); % Set background color
    set(gca,'XColor', 'none','YColor','none') % Remove axis's
    bars(bars ~= 0) = 0;
    bars_new = bars; % Return empty bars
    p_new = max(p, p_old - maxY/50); % Return p_new
    return;
    