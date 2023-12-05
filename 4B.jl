matches = map(A -> length(findall(in(A[begin:findfirst(x -> x=="|", A)-1]), A[findfirst(x -> x=="|", A)+1:end])), map(x -> filter!(!isempty, split(x, " ")[3:end]), readlines(open("input/4.txt", "r"))))
numbers = fill(1, length(matches)) 
map(i -> map(j -> numbers[j] += numbers[i], Array(i+1:i+matches[i])), Array(1:length(matches)))
println(sum(numbers))
