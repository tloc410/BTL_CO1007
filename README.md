# SUBGRAPH ISOMORPHISM: IDENTIFYING A GIVEN SUB-GRAPH IN A LARGER GRAPH

## Abstract
Ngày này, các nền tảng Thương mại điện tử hoặc được biết đến là các trang web thương mại
trực tuyến là một nền tảng nơi nhiều công ty bên thứ ba cung cấp dịch vụ hoặc hàng hóa. Nền
tảng này chịu trách nhiệm cung cấp các dịch vụ giúp thực hiện giao dịch giữa những người dùng
của nó, tức người mua và người bán. Các nền tảng trực tuyến như Amazon mang đến cho người
mua cơ hội thực hiện mua sắm trên cùng một nền tảng mà không cần rời khỏi trang web hoặc
ứng dụng. Những thị trường này thu thập và lưu trữ dữ liệu về mọi hoạt động của người dùng
để phân tích hành vi mua sắm của khách hàng, từ đó giúp cải thiện các hoạt động tiếp thị như
đặt sản phẩm, bán hàng kết hợp, hoặc giữ chân khách hàng. Phân tích giỏ hàng (Market Basket
Analysis - MBA) đã là một kỹ thuật khai thác dữ liệu có giá trị trong nhiều thập kỷ đối với các
nhà tiếp thị và nhà nghiên cứu, từ đó nắm được nhu cầu sử dụng sản phẩm và thị hiếu của khách
hàng và bắt đầu đưa ra những phân tích chuyên sâu để lập nên những chiến dịch marketing phù
hợp. Nắm bắt được tình hình thực tế như vậy nhóm chúng em đã quyết định chọn bộ dataset
"Amazon product co-purchasing network", một bộ dữ liệu thể hiện cho mạng lưới mua sắm trên
nền tảng Amazon. Bên cạnh đó, trong bài báo cáo này, chúng em cũng trình bày những hiểu biết
của mình về hai chủ đề đầu tiên của phần Writing Projects trong sách Discrete Mathematics anh
Its Applications tái bản lần thứ 8 của tác giả Kenneth H. Rosen. Đó là "Nguồn gốc và sự phát
triển của lý thuyết đồ thị trước năm 1900" và "Những ứng dụng của lý thuyết đồ thị trong việc
nghiên cứu hệ sinh thái"

## Dataset

Bộ dữ liệu được sử dụng là [amazon0302.tsv](http://graphchallenge.mit.edu/data-sets#SNAPDatasets)

Mạng lưới trong bộ dataset này được thu thập thông qua việc lướt web trên trang
web Amazon. Nó dựa trên tính năng "Khách hàng đã mua cùng sản phẩm này cũng đã
mua cùng với sản phẩm khác" của trang web Amazon. Nếu sản phẩm i thường xuyên
được mua cùng với sản phẩm j, đồ thị sẽ chứa một cạnh hướng từ i đến j.
Bộ dữ liệu có 262111 đỉnh, mỗi đỉnh thể hiện cho một sản phẩm, 1234877 cạnh, mỗi
cạnh thể hiện cho hành vi mua của khách hàng trên nền tảng, 
