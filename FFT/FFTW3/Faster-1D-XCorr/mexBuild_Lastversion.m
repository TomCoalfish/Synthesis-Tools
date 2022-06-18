function mexBuild_Lastversion
% if recompile == 1
clear;
close all;
clear mex;

delete MyFFTinterp_debug_mexipeusctstudent4.mexw64
% % lcean up potentially existing DLL
 try MyFFTinterp_debug_mexipeusctstudent4([1 1],[1 1],[0 0],2,[1 1],[2 2],[0 0],-1); catch, end
% % path('.\WISDOM_FOLDER','W:\abid\USCT\Source_code');
% 
clear
% close all
RealData=0;
if RealData==1
% Load data
dataFolder = 'W:\abid\USCT\InputData';
% Parameters

file = fullfile(dataFolder,sprintf('Input.mat'));

load(file,'AScanList','AScanRefList','distList','distRefList','startSearchRefList','endSearchRefList','startSearchList', 'endSearchList','soundSpeedRefList','soundSpeedList');


end_s_resample=int32(endSearchRefList);
start_s_resample=int32(startSearchList);
A=single(AScanRefList');
B=single(AScanList');
A_matlab=A;
B_matlab=B;
[sizesChange,Multiplicity]=size(A);
end
outputfilename=[];
[~,outputfilename]=system('hostname');
outputfilename(end)=[];
basefilename='MyFFTinterp_debug_mex';
outputfilename=cat(2,basefilename,outputfilename, '.mex');
% 
mex -setup C++
mex('-O', '-output', outputfilename, '-IW:\abid\USCT\SignalDetection\SignalDetection\', ['W:/abid/USCT/SignalDetection/SignalDetection/' basefilename '.cpp'], 'W:/abid/USCT/SignalDetection/SignalDetection/MyinterpFFT.cpp', 'W:/abid/USCT/SignalDetection/SignalDetection/FirstPulseDetection.cpp' , '-LW:\abid\USCT\Validation_C_MATLAB\', 'libfftw3f-3.lib'); %, 'libfftw3-3.lib'

% end

% %% %%%%%%%%%%%%%%%%%%%%%%%Mutiple plan FFTW%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
loops=100;

RESAMPLE_FACTOR=1;
counter=0;
nThread=[7];
if RealData==0
rand_init=1;
timeMyXcorr=[];
sizesChange = 3024;
Multiplicity=([1]);%*4;
end



for nThread_i=nThread%:-1:1
    %        nThread_i
    for Multiplicity_i=Multiplicity;
        Multiplicity_i
        lag_max_i=int32(zeros(1,Multiplicity_i));
        
        for j=3000
            if RealData==0
                start_s=(3*ones(1,Multiplicity_i)');
                end_s=((j*ones(1,Multiplicity_i))');
                start_s_resample=int32((start_s'-ones(1,Multiplicity_i))*RESAMPLE_FACTOR+ones(1,Multiplicity_i));
                end_s_resample=int32((end_s'-ones(1,Multiplicity_i))*RESAMPLE_FACTOR+ones(1,Multiplicity_i));
            end
            j
            Mycorr=(single(zeros(RESAMPLE_FACTOR*j,Multiplicity_i)));
            if RealData==0
                
                if rand_init~=1
                    A = single((1:1:j)');
                    A = repmat(A,[1 Multiplicity_i]);
                else
                    A = single(rand(j,Multiplicity_i));
                end
                A=A-mean(A,1);
                %                      A=zeros(size(A));
                %                     A=diag(ones(1,size(A,1)));
                %                     A=single(A);
                B=zeros(size(A));
                B(1,:)=ones(1,size(A,2));
                B = single(B);
                
            end
            clear mex;
            for i=1:loops
                for x=1:10000 end;
                %                     i
                %                           %%%%%%%%%%%%%%%%%%%%MATLAB implementation%%%%%%%%%%%%%%
                %                      tic
                %                 [ seg1r ] = resample2D( double(A),RESAMPLE_FACTOR );
                %                 [ seg2r ] = resample2D( double(B),RESAMPLE_FACTOR );
                %                 [crr,lags] = xcorr2D(seg2r,seg1r);
                %                 timeEval_matlab=toc;
                %                 tic
                                Man_corr=[];
                                Man_corr= ifft((fft(A)).*(conj(fft(B))));%./abs(fft(A));
                %
                                Man_corr1=interpft( double(Man_corr), RESAMPLE_FACTOR.*length(Man_corr),1)./(RESAMPLE_FACTOR);
%                                 timeEval_matlab_intern=toc;
                %%%%%%%%%%%%%%%%%%%%C/C++ implementation%%%%%%%%%%%%%%
                
                tic
                A1=A';
                B1=B';
                eval([outputfilename(1:end-4) '(A,B,Mycorr,RESAMPLE_FACTOR,start_s_resample, end_s_resample,lag_max_i,(nThread_i))']);
                time_exhaustive(i,j,Multiplicity_i)=toc;
                % timeEval_C=toc;
                
                %                     fprintf('Iteration number : %d\n ',i);
                
                %                     fprintf('Time execution for Matlab : %d\n for internal Matlab: %d \n for C: %d\n',timeEval_matlab,timeEval_matlab_intern,timeEval_C );
                
                
                
                %                     LoadingPerformance(i,nThread_i,Multiplicity_i)=(Multiplicity_i*j*8)./time_exhaustive(i,j,nThread_i,Multiplicity_i);
                %                     LoadingPerformance(i,j)=(Multiplicity_i*j*8)./time_exhaustive(i,j,nThread_i,Multiplicity_i);
                
                % figure; plot(1:30240,Mycorr(:,1100),1:30240,fftshift(crr(length(crr)/4:length(crr)*(3/4),1100)));
                
                
            end
            
        end
        
    end
end
      figure;plot(sizesChange,median(time_exhaustive(3:end,sizesChange,Multiplicity),1),'*');
%      save(fullfile('W:\abid\USCT\Source_code\Performance Evaluation\',sprintf('fftwSizeChangeWholeProcess3000_4096Over2000loops.mat')),'time_exhaustive','-v7.3');
nThread=7; 
     for o=3000:4096
         try close all; catch, end
          f=figure(1); histogram(time_exhaustive(3:end,o,nThread),200);
%         figure; hist(time_exhaustive(3:end,o,nThread),100);
        md=median(time_exhaustive(3:end,o,nThread));
        mn=min(time_exhaustive(3:end,o,nThread),[],1);
        mu=mean(time_exhaustive(3:end,o,nThread),1);
        stdv=std(time_exhaustive(3:end,o,nThread));
        hold on ;
        plot([md,md],ylim,'r','LineWidth',2), 
        plot([mn,mn],ylim,'b','LineWidth',2),
        plot([mu,mu],ylim,'g','LineWidth',2), 
        hold off;
        legend('histogram','median','min','mean');
        xlabel('Absolute time execution (s)'); % x-axis label
        ylabel('Number of occurences'); % y-axis label
        title(sprintf('Histogram representation over 200 loops, Ascan size= %d',o));

        mnlabel=sprintf('Min -- %3.2d s', mn);
        mdlabel=sprintf('Median -- %3.2d s', md);
        mulabel=sprintf('Mean -- %3.2d s', mu);
        pause(0.5);
        stdlabel=sprintf('Std Deviation -- %3.2d', stdv);
        h=annotation('textbox',[0.58 0.55 0.1 0.1]);
        set(h,'String',{mnlabel,mulabel, mdlabel, stdlabel});
%  saveas(f,[fullfile('W:\abid\USCT\Source_code\Performance Evaluation\WholeProcessEvaluation\HistogramOver2000Loops\'),sprintf('AscanSize%d.pdf',o)],'pdf');
%  saveas(f,[fullfile('W:\abid\USCT\Source_code\Performance Evaluation\WholeProcessEvaluation\HistogramOver2000Loops\'),sprintf('AscanSize%d.fig',o)],'fig');

     end
     if (length(sizesChange)~=1)
        figure;hold on;plot(2:loops,(time_exhaustive(3:end,sizesChange,nThread,Multiplicity)),'*-');
            figure;plot(sizesChange,median(time_exhaustive(3:end,sizesChange,nThread,Multiplicity),1),'*');
            hold on;plot(sizesChange,min(time_exhaustive(3:end,sizesChange,nThread,Multiplicity),[],1),'*');
%             hold on;plot(sizesChange,mean(time_exhaustive(3:end,sizesChange,nThread,Multiplicity),1),'*');
%             hold on;plot(sizesChange,ones(1,length(sizesChange))*0.0003221);
            legend('Median','Min');
        ylabel('Absolute time execution (s)'); % y-axis label
        xlabel('Ascan size Change'); % x-axis label
        title(sprintf('Absolute time execution along size change over 2000 loops'));
     end
     if (length(Multiplicity)~=1)
         figure;plot(Multiplicity,squeeze(median(time_exhaustive(3:end,sizesChange,nThread,Multiplicity),1))./Multiplicity','*-');
         hold on;plot(Multiplicity,squeeze(min(time_exhaustive(3:end,sizesChange,nThread,Multiplicity),[],1))./Multiplicity','*-');
         legend('Median','Min');
         ylabel('Time execution per Ascan (s)'); % y-axis label
         xlabel('Number of Ascans Processed (Block size; multiplicity)'); % x-axis label
         title(sprintf('Time execution per Ascan along Multiplicity over 20 loops'));
     end
%     c=0;
%     LoadingPerformance_=[];
%     for sizesChange_i=sizesChange;
%         c=c+1;
%         LoadingPerformance_(:,c)=LoadingPerformance(:,sizesChange_i);
%     end
    c=0;
    time_exhaustive_=[];
    for sizesChange_i=sizesChange;
        c=c+1;
        time_exhaustive_(:,c,nThread,Multiplicity)=time_exhaustive(:,sizesChange_i,nThread,Multiplicity);
    end
c=0
for i=sizesChange;
     c=c+1;
    TimePerSample__(:,c,nThread,Multiplicity) =time_exhaustive(:,i,nThread,Multiplicity)./i;
end

figure;plot(sizesChange,median(TimePerSample__(3:end,:,nThread,Multiplicity),1),'*');


figure;imagesc(squeeze(median(TimePerAscan(1:end,sizesChange,:,:),1)));

figure;imagesc(repmat((sizesChange*Multiplicity)',1,16)'./squeeze(median(time_exhaustive(3:end,sizesChange,:,:),1)));
figure;imagesc(repmat((sizesChange*Multiplicity)',1,32)'./squeeze(mean(time_exhaustive(2:end,sizesChange,:,:),1)));
[a,b]=max(max(repmat((sizesChange*Multiplicity)',1,16)'./squeeze(median(time_exhaustive(3:end,sizesChange,:,:),1))))
c=0;
LoadingPerformance_=[];
for Multiplicity_i=Multiplicity;
    c=c+1;
    LoadingPerformance_(:,c)=LoadingPerformance(:,nThread_i,Multiplicity_i);
end

            DataSize=(Multiplicity*sizesChange*8);
            figure;plot(nThread,max(LoadingPerformance_,[],1));
        
            figure;plot(DataSize,max(LoadingPerformance_,[],1),'*-');
            
            figure;plot(sizesChange,median(LoadingPerformance_,1),'*--');
            figure;plot(sizesChange,median(LoadingPerformance_,1),'*--');
            hold on ; plot(sizesChange,ones(1,length(DataSize))*8.749e7)
            hold on ; plot(sizesChange,ones(1,length(DataSize))*1.671e7)
            
             figure;plot(nThread,min(time_exhaustive(:,:,Multiplicity_i),[],1));
             hold on ;
             plot(sizesChange,ones(1,length(sizesChange))*0.0003242)
             
             figure;plot(sizesChange,min(time_exhaustive(:,sizesChange),[],1),'*');
            
         
             
             figure;plot(sizesChange,max(LoadingPerformance_,[],1),'*');
            
end



% %****Last modified 12/06/2018****************************Chaine complete sans paadding****************************
% while(1)
%     counter=counter+1
%     for nThread_i=7%:-1:1
%         
%         for Multiplicity_i=Multiplicity;
%             Mycorr=(single(zeros(RESAMPLE_FACTOR*sizesChange,Multiplicity_i)));%Mycorr=single(zeros(RESAMPLE_FACTOR*sizesChange,Multiplicity_i));
%             lag_max_i=int32(zeros(1,Multiplicity_i));
%             
%             start_s=(3*ones(1,Multiplicity_i)');
%             end_s=((sizesChange*ones(1,Multiplicity_i))');
%             start_s_resample=int32((start_s-ones(1,Multiplicity_i))*RESAMPLE_FACTOR+ones(1,Multiplicity_i));
%             end_s_resample=int32((end_s-ones(1,Multiplicity_i))*RESAMPLE_FACTOR+ones(1,Multiplicity_i));
%             for j=sizesChange
%                 if rand_init~=1
%                     A = single((1:1:j)');
%                     A = repmat(A,[1 Multiplicity_i]);
%                 else
%                     A = single(rand(j,Multiplicity_i));
%                 end
%                 B = A;
%                 clear mex;
%                 for i=1:loops
%                    
%                    
%                     tic
%                     eval([outputfilename(1:end-4) '(A,B,Mycorr,RESAMPLE_FACTOR,start_s_resample, end_s_resample,lag_max_i,(nThread_i))']);
%                     time_exhaustive(i,Multiplicity_i)=toc;
%                     LoadingPerformance(i,Multiplicity_i)=(Multiplicity_i*3024*8)./time_exhaustive(i,Multiplicity_i);
%                              
% 
% 
%                    Check=[];
%                     for w=1:Multiplicity_i
%                         [~,index]=max([zeros(start_s_resample(w)-1,1);Mycorr(start_s_resample(w):end_s_resample(w),w)]);
%                         Check(w)=(index==lag_max_i(w));
%                     end
%                     somme=sum(Check);
%                     if (somme~=Multiplicity)
%                         disp('error!');
%                     end
%                     
%                 end
%             end
%             
%         end
%         
%     end
%    
% end

