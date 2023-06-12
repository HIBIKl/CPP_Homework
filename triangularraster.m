% Use: compute "blackNodeNum" 
% Only for binary bmp

% [Q]=triangularraster(3,'fivestar8_binary.bmp');
% [Q]=triangularraster(4,'fivestar16_binary.bmp');
% [Q]=triangularraster(5,'fivestar32_binary.bmp');
% [Q]=triangularraster(6,'fivestar64_binary.bmp');
% [Q]=triangularraster(7,'fivestar128_binary.bmp');
% [Q]=triangularraster(8,'fivestar256_binary.bmp');
% [Q]=triangularraster(9,'fivestar512_binary.bmp');

% [Q]=triangularraster(3,'sixstar8_binary.bmp');
% [Q]=triangularraster(4,'sixstar16_binary.bmp');
% [Q]=triangularraster(5,'sixstar32_binary.bmp');
% [Q]=triangularraster(6,'sixstar64_binary.bmp');
% [Q]=triangularraster(7,'sixstar128_binary.bmp');
% [Q]=triangularraster(8,'sixstar256_binary.bmp');
% [Q]=triangularraster(9,'sixstar512_binary.bmp');



function  [num_of_total_mix]=triangularraster(n,f)
tic
picture=f;
f=imread(f);
f=double(f);

% f=zeros(8,8)
% 
% f =[
%     1     0     0     0     0     0     0     1
%     1     0     0     0     0     0     0     0
%     1     0     0     0     0     0     0     0
%     1     1     1     0     0     0     0     0
%     1     1     1     1     0     0     0     0
%     0     1     1     0     0     0     0     0
%     0     0     1     0     1     0     0     0
%     0     0     0     0     0     0     1     0
% ]
% % f=[
%      1     1     1     1     1     1     1     1
%      1     1     1     1     1     1     1     1
%      1     1     1     0     0     1     1     1
%      1     0     0     0     0     0     0     1
%      1     1     0     0     0     0     1     1
%      1     1     0     0     0     0     1     1
%      1     1     0     1     1     0     1     1
%      1     1     1     1     1     1     1     1
%  ]
% f=ones(8,8)

mark=f;
org=f;

% n=3

size=2^n;% the size of the picture is size * size 
num_of_upper_triangular=0;
num_of_lower_triangular=0;
num_of_total_triangular=0;
for var_sp_x=1:size-1
    for var_sp_y=1:size-1
        %         var_sp_x=6;
        %         var_sp_y=4;
        for step=size-1:-1:1
            %     step=2;
            if (var_sp_x+step<=size) && (var_sp_y+step<=size)
                f =mark;
                f=f(var_sp_x:var_sp_x+step,var_sp_y:var_sp_y+step);
                size_temp=step+1;
                
                %***!mcc*************************************************************** 
                for k=0:(size_temp-2)
                    % k=6
                    upper_triangular=triu(f,k);
                    if sum(sum(upper_triangular))==0
                        num_of_upper_triangular=num_of_upper_triangular+1;
                        num_of_total_triangular=num_of_total_triangular+1;
                        x1=1;y1=k+1;
                        x2=size_temp-k;y2=size_temp;
                        x3=1;y3=size_temp;
                        x1_abs=x1+var_sp_x-1;
                        y1_abs=y1+var_sp_y-1;
                        x2_abs=x2+var_sp_x-1;
                        y2_abs=y2+var_sp_y-1;
                        Q_tri{num_of_total_triangular}={0,x1_abs,y1_abs,x2_abs,y2_abs};
                        for i=x1:x2
                            for j=(i+k):y2
                                mark(i+var_sp_x-1,j+var_sp_y-1)=8;
                            end
                        end
                    end
                    break;
                end
                mark;
                %******************************************************************  
                
                %****************************************************************** 
                for k=0:-1:(-size_temp+2)
                    %      k=-6
                    lower_triangular=tril(f,k);
                    if sum(sum(lower_triangular))==0
                        num_of_lower_triangular=num_of_lower_triangular+1;
                        num_of_total_triangular=num_of_total_triangular+1;
                        x1=1-k;y1=1;
                        x2=size_temp;y2=size_temp+k;
                        x3=size_temp;y3=1;
                        x1_abs=x1+var_sp_x-1;
                        y1_abs=y1+var_sp_y-1;
                        x2_abs=x2+var_sp_x-1;
                        y2_abs=y2+var_sp_y-1;
                        Q_tri{num_of_total_triangular}={1,x1_abs,y1_abs,x2_abs,y2_abs};
                        for i=x1:x2
                            for j=1:i+k
                                mark(i+var_sp_x-1,j+var_sp_y-1)=9;
                            end
                        end
                    end 
                    break;
                end
                mark;
                %****************************************************************** 
                
                % imshow(uint8(f*255))
                
                % celldisp(Q)
            end
            
        end
    end
end
org;
mark_tri=mark;
decom_result=org-mark_tri;
num_of_upper_triangular;
num_of_lower_triangular;
num_of_total_triangular;

% *************************************************************************

%    part two

% *************************************************************************

f=mark_tri;
blackNodeNum=0;
line_num=0;
point_num=0;
Width0=1; Length0=1;
for x=1:2^n
    for y=1:2^n
        sp_y=y;
        sp_x=x;
        if(f(x,y)==0)
            % Length=1;Width=1;MaxArea=1;
            Length=1;Width=1;MaxArea=0;
            last=0;
            for j=y:2^n
                Length0=0;
                for k=x:2^n
                    if not(j==y) &&(k-sp_x+1>last) break;end
                    if ~(f(k,j)==0)  break; end
                    Length0=Length0+1;
                end %end for k=x:2^n
                if j==y  last=Length0; end;
                if Length0<last last=Length0; end;
                if ~(f(x,j)==0)  break; end
                Width0=Width0+1;
                Length=last;
                Width=j-sp_y+1;
                Area=Length*Width;
                if Area>MaxArea %  if Area>MaxArea
                    MaxArea =Area;
                    MaxLength=last;
                    MaxWidth=j-sp_y+1;
                end
            end % for j=y:2^n

            if MaxLength*MaxWidth==1 
                point_num=point_num+1;
            else
                line_num=line_num+1;
            end
            blackNodeNum=blackNodeNum+1;
            Q{blackNodeNum}={x,y,MaxLength,MaxWidth};
            for a=x:x+MaxLength-1
                for b=y:y+MaxWidth-1;
                    f(a,b)=7;
                end
            end
        end
    end
end;
% decom_result=org-f
% celldisp(Q)
point_num;
line_num;
num_of_total_rectangle=blackNodeNum;
mark_tri_rec=f;

num_of_total_mix= num_of_total_triangular
% num_of_total_mix=num_of_total_rectangle + num_of_total_triangular
%triangular_ratio=4^n/(point_num*n + line_num*2*n + num_of_total_triangular*(2*n+1))

% %rect_node_num=rectangleraster2(n,picture)
% %rect_ratio=4^n/(2*n*rect_node_num)
% 
% %quad_node_num=quadtreezyp2(picture)
% %quadtree_ratio=4^n/((3*n-1)*quad_node_num)
% 
% %ratio_triangular_to_quadtree=triangular_ratio/quadtree_ratio
% %ratio_rectangle_to_quadtree=rect_ratio/quadtree_ratio
% 完全不知道为什么这段代码放在这，没有任何rectangleraster2的信息


%************************************************  The following is the decoder ! ************************************ 
res=ones(size,size);
% %*********************************************** triangulars  are decoded 
for k=1:num_of_total_triangular

    flag=Q_tri{k}{1};
    x1_abs=Q_tri{k}{2};
    y1_abs=Q_tri{k}{3};
    x2_abs=Q_tri{k}{4};
    y2_abs=Q_tri{k}{5};

    switch flag
        case 0 % upper triangular 
            step=0;
            for i=x1_abs:x2_abs
                for j=y1_abs+step:y2_abs
                    %                         res(i,j)=8;
                    res(i,j)=0;
                end
                step=step+1;
            end  

        case 1 % lower triangular  
            step=0;
            for i=x1_abs:x2_abs
                for j=y1_abs:y1_abs+step
                    %                         res(i,j)=9;
                    res(i,j)=0;
                end
                step=step+1;
            end  

        otherwise

    end

end

%*********************************************** lines and points  are decoded 
for j=1:blackNodeNum
    x=Q{j}{1};
    y=Q{j}{2};
    MaxLength=Q{j}{3};
    MaxWidth=Q{j}{4};

    for a=x:x+MaxLength-1
        for b=y:y+MaxWidth-1;
            %             res(a,b)=7;
            res(a,b)=0;
        end
    end
end 

%mark_tri_rec;
%res;
%diff=sum(sum(res-org))

imshow(uint8(org*255)),title('orignal picture')
figure
imshow(uint8(res*255)),title('restructed picture')

% %************************************************                                  ************************************  

toc