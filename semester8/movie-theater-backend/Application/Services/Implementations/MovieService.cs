using Minio;
using Application.Services.Interfaces;
using Application.Dto;
using Domain.Repositories;
using Domain.Entities;
using Minio.DataModel.Args;

namespace Application.Services.Implementations;

public class MovieService : IMovieService
{
    protected readonly IMovieRepository _movieRepository;
    protected readonly IMinioClient _minioClient;

    protected readonly string _movieBucket = "movies";
    protected readonly string _posterBucket = "posters";

    public  MovieService(IMinioClient minioClient, IMovieRepository movieRepository)
    {
       _minioClient = minioClient;
       _movieRepository = movieRepository;
    }

    public async Task<IEnumerable<MovieDto>> GetMoviesAsync(float? minRating)
    {
        IEnumerable<Movie> movies = await _movieRepository.Get(minRating);
        List<MovieDto> dtos = new();

        foreach (var movie in movies)
        {
            PresignedGetObjectArgs movieArgs = new PresignedGetObjectArgs()
                .WithBucket(_movieBucket)
                .WithObject(movie.MoviePath);

            PresignedGetObjectArgs posterArgs = new PresignedGetObjectArgs()
                .WithBucket(_posterBucket)
                .WithObject(movie.PosterPath);

            dtos.Add(new MovieDto 
            { 
                Title = movie.Title, 
                Annotation = movie.Annotation,
                MovieLink = await _minioClient.PresignedGetObjectAsync(movieArgs),
                PosterLink =  await _minioClient.PresignedGetObjectAsync(posterArgs)
            });
        }

        return dtos;
    }

    public async Task UploadMovie(MovieUploadDto movieInfo)
    {
        Task[] tasks = {
            UploadFile(_posterBucket, movieInfo.Poster),
            UploadFile(_movieBucket, movieInfo.Movie),
            _movieRepository.Add(new Movie 
            {
                Title = movieInfo.Title,
                Annotation = movieInfo.Annotation,
                MoviePath = movieInfo.Movie.Name,
                PosterPath = movieInfo.Poster.Name
            })
         };

        await Task.WhenAll(tasks);
        _movieRepository.Save();
    }

    protected async Task UploadFile(string bucket, IFormFile file)
    {
        using (var stream = file.OpenReadStream())
        {
            PutObjectArgs args = new PutObjectArgs()
                .WithBucket(bucket)
                .WithStreamData(stream)
                .WithObject(file.Name)
                .WithObjectSize(file.Length)
                .WithContentType(file.ContentType);

            if (!await _minioClient.BucketExistsAsync(new BucketExistsArgs().WithBucket(bucket)))
                await _minioClient.MakeBucketAsync(new MakeBucketArgs().WithBucket(bucket));

            await _minioClient.PutObjectAsync(args);
        }
    }
}
