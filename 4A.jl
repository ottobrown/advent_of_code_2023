println(sum(map(A -> (big(2)^length(findall(in(A[begin:findfirst(x -> x=="|", A)-1]), A[findfirst(x -> x=="|", A)+1:end]))) ÷ 2,  map(x -> filter!(!isempty, split(x, " ")[3:end]), readlines(open("input/4.txt", "r"))))))