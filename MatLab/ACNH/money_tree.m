clc
clear all
profit = @(money) (30e3 * 0.7) + (3 * money * 0.3) - money;
profit(10e3)
profit(20e3)
profit(30e3)
profit(40e3)
profit(50e3)
profit(99e3)