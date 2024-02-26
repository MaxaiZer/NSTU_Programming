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

    public async Task<IEnumerable<MovieDto>> GetMoviesAsync(int? limit, int? offset, float? minRating)
    {
        IEnumerable<Movie> movies = await _movieRepository.Get(limit, offset, minRating);
        List<MovieDto> dtos = new();

        foreach (var movie in movies)
        {
            PresignedGetObjectArgs movieArgs = new PresignedGetObjectArgs()
                .WithBucket(_movieBucket)
                .WithObject(movie.MovieObjectName);

            PresignedGetObjectArgs posterArgs = new PresignedGetObjectArgs()
                .WithBucket(_posterBucket)
                .WithObject(movie.PosterObjectName);

            dtos.Add(new MovieDto 
            { 
                Title = movie.Title, 
                Annotation = movie.Annotation,
                MovieUrl = await _minioClient.PresignedGetObjectAsync(movieArgs),
                PosterUrl =  await _minioClient.PresignedGetObjectAsync(posterArgs)
            });
        }

        return dtos;
    }

    public async Task<MovieDto?> GetMovieByIdAsync(int id)
    {
        Movie? movie = await _movieRepository.GetById(id);
        if (movie == null) return null;

        PresignedGetObjectArgs movieArgs = new PresignedGetObjectArgs()
            .WithBucket(_movieBucket)
            .WithObject(movie.MovieObjectName);

        PresignedGetObjectArgs posterArgs = new PresignedGetObjectArgs()
            .WithBucket(_posterBucket)
            .WithObject(movie.PosterObjectName);

        return new MovieDto
        {
            Title = movie.Title, 
            Annotation = movie.Annotation,
            MovieUrl = await _minioClient.PresignedGetObjectAsync(movieArgs),
            PosterUrl =  await _minioClient.PresignedGetObjectAsync(posterArgs)
        };
    }
 
    public async Task UploadMovieAsync(MovieUploadDto movieInfo)
    {
        Task[] tasks = {
            UploadFile(_posterBucket, movieInfo.Poster),
            UploadFile(_movieBucket, movieInfo.Movie),
            _movieRepository.Add(new Movie 
            {
                Title = movieInfo.Title,
                Annotation = movieInfo.Annotation,
                MovieObjectName = movieInfo.Movie.Name,
                PosterObjectName = movieInfo.Poster.Name
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
